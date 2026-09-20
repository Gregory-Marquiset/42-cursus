export type RgbaFrame = Uint8Array;

export type GifOptions = {
  width: number;
  height: number;
  delayCentiseconds: number;
};

export type ProgressHandler = (fraction: number) => void;

const MAX_COLORS = 256;

const PALETTE_SAMPLE_BUDGET = 24000;

function buildPalette(frames: RgbaFrame[]): Uint8Array {
  const samples = sampleColors(frames);
  const count = samples.length / 3;
  const palette = new Uint8Array(MAX_COLORS * 3);
  if (count === 0) return palette;

  const order = new Uint32Array(count);
  for (let i = 0; i < count; i += 1) order[i] = i;

  const boxes: Array<[number, number]> = [[0, count]];

  while (boxes.length < MAX_COLORS) {
    let widest = -1;
    let widestSpread = 0;
    let widestChannel = 0;

    for (let b = 0; b < boxes.length; b += 1) {
      const [start, end] = boxes[b];
      if (end - start < 2) continue;
      const { channel, spread } = dominantChannel(samples, order, start, end);
      if (spread > widestSpread) {
        widest = b;
        widestSpread = spread;
        widestChannel = channel;
      }
    }

    if (widest < 0 || widestSpread === 0) break;

    const [start, end] = boxes[widest];
    order
      .subarray(start, end)
      .sort((a, b) => samples[a * 3 + widestChannel] - samples[b * 3 + widestChannel]);

    const middle = (start + end) >> 1;
    boxes.splice(widest, 1, [start, middle], [middle, end]);
  }

  for (let b = 0; b < boxes.length; b += 1) {
    const [start, end] = boxes[b];
    let red = 0;
    let green = 0;
    let blue = 0;
    for (let i = start; i < end; i += 1) {
      const at = order[i] * 3;
      red += samples[at];
      green += samples[at + 1];
      blue += samples[at + 2];
    }
    const size = end - start;
    palette[b * 3] = Math.round(red / size);
    palette[b * 3 + 1] = Math.round(green / size);
    palette[b * 3 + 2] = Math.round(blue / size);
  }
  return palette;
}

function dominantChannel(
  samples: Uint8Array,
  order: Uint32Array,
  start: number,
  end: number,
): { channel: number; spread: number } {
  const min = [255, 255, 255];
  const max = [0, 0, 0];
  for (let i = start; i < end; i += 1) {
    const at = order[i] * 3;
    for (let c = 0; c < 3; c += 1) {
      const value = samples[at + c];
      if (value < min[c]) min[c] = value;
      if (value > max[c]) max[c] = value;
    }
  }
  let channel = 0;
  let spread = 0;
  for (let c = 0; c < 3; c += 1) {
    const width = max[c] - min[c];
    if (width > spread) {
      spread = width;
      channel = c;
    }
  }
  return { channel, spread };
}

function sampleColors(frames: RgbaFrame[]): Uint8Array {
  const totalPixels = frames.reduce((sum, frame) => sum + frame.length / 4, 0);
  if (totalPixels === 0) return new Uint8Array(0);

  const step = Math.max(1, Math.floor(totalPixels / PALETTE_SAMPLE_BUDGET));
  const collected: number[] = [];
  for (const frame of frames) {
    const pixels = frame.length / 4;
    for (let pixel = 0; pixel < pixels; pixel += step) {
      const at = pixel * 4;
      collected.push(frame[at], frame[at + 1], frame[at + 2]);
    }
  }
  return Uint8Array.from(collected);
}

function createColorMapper(palette: Uint8Array): (r: number, g: number, b: number) => number {
  const cache = new Int16Array(32768).fill(-1);

  return (r, g, b) => {
    const key = ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3);
    const known = cache[key];
    if (known >= 0) return known;

    let best = 0;
    let bestDistance = Number.POSITIVE_INFINITY;
    for (let i = 0; i < MAX_COLORS; i += 1) {
      const dr = r - palette[i * 3];
      const dg = g - palette[i * 3 + 1];
      const db = b - palette[i * 3 + 2];
      const distance = dr * dr + dg * dg + db * db;
      if (distance < bestDistance) {
        bestDistance = distance;
        best = i;
      }
    }
    cache[key] = best;
    return best;
  };
}

function compress(indices: Uint8Array, minCodeSize: number): Uint8Array {
  const clearCode = 1 << minCodeSize;
  const endCode = clearCode + 1;

  const out: number[] = [];
  let register = 0;
  let registerBits = 0;
  let codeSize = minCodeSize + 1;

  const emit = (code: number): void => {
    register |= code << registerBits;
    registerBits += codeSize;
    while (registerBits >= 8) {
      out.push(register & 0xff);
      register >>= 8;
      registerBits -= 8;
    }
  };

  let table = new Map<number, number>();
  let nextCode = endCode + 1;

  emit(clearCode);

  let prefix = indices[0];
  for (let i = 1; i < indices.length; i += 1) {
    const next = indices[i];
    const key = (prefix << 8) | next;
    const known = table.get(key);
    if (known !== undefined) {
      prefix = known;
      continue;
    }

    emit(prefix);
    if (nextCode === 4096) {
      emit(clearCode);
      table = new Map();
      nextCode = endCode + 1;
      codeSize = minCodeSize + 1;
    } else {
      if (nextCode >= 1 << codeSize && codeSize < 12) codeSize += 1;
      table.set(key, nextCode);
      nextCode += 1;
    }
    prefix = next;
  }

  emit(prefix);
  emit(endCode);
  if (registerBits > 0) out.push(register & 0xff);

  return Uint8Array.from(out);
}

class ByteSink {
  private buffer = new Uint8Array(64 * 1024);
  private length = 0;

  private reserve(extra: number): void {
    if (this.length + extra <= this.buffer.length) return;
    let capacity = this.buffer.length;
    while (capacity < this.length + extra) capacity *= 2;
    const grown = new Uint8Array(capacity);
    grown.set(this.buffer.subarray(0, this.length));
    this.buffer = grown;
  }

  byte(value: number): void {
    this.reserve(1);
    this.buffer[this.length] = value & 0xff;
    this.length += 1;
  }

  short(value: number): void {
    this.byte(value);
    this.byte(value >> 8);
  }

  ascii(text: string): void {
    for (let i = 0; i < text.length; i += 1) this.byte(text.charCodeAt(i));
  }

  raw(bytes: Uint8Array): void {
    this.reserve(bytes.length);
    this.buffer.set(bytes, this.length);
    this.length += bytes.length;
  }

  blocks(bytes: Uint8Array): void {
    let offset = 0;
    while (offset < bytes.length) {
      const size = Math.min(255, bytes.length - offset);
      this.byte(size);
      this.raw(bytes.subarray(offset, offset + size));
      offset += size;
    }
    this.byte(0);
  }

  toBytes(): Uint8Array {
    return this.buffer.slice(0, this.length);
  }
}

export async function encodeGif(
  frames: RgbaFrame[],
  options: GifOptions,
  onProgress?: ProgressHandler,
): Promise<Uint8Array> {
  if (frames.length === 0) throw new Error('Aucune image à encoder.');

  const { width, height, delayCentiseconds } = options;
  const palette = buildPalette(frames);
  const toPaletteIndex = createColorMapper(palette);

  const sink = new ByteSink();

  sink.ascii('GIF89a');
  sink.short(width);
  sink.short(height);
  sink.byte(0xf7);
  sink.byte(0);
  sink.byte(0);
  sink.raw(palette);

  sink.byte(0x21);
  sink.byte(0xff);
  sink.byte(11);
  sink.ascii('NETSCAPE2.0');
  sink.byte(3);
  sink.byte(1);
  sink.short(0);
  sink.byte(0);

  const indices = new Uint8Array(width * height);

  for (let f = 0; f < frames.length; f += 1) {
    const frame = frames[f];
    for (let pixel = 0; pixel < indices.length; pixel += 1) {
      const at = pixel * 4;
      indices[pixel] = toPaletteIndex(frame[at], frame[at + 1], frame[at + 2]);
    }

    sink.byte(0x21);
    sink.byte(0xf9);
    sink.byte(4);
    sink.byte(0);
    sink.short(delayCentiseconds);
    sink.byte(0);
    sink.byte(0);

    sink.byte(0x2c);
    sink.short(0);
    sink.short(0);
    sink.short(width);
    sink.short(height);
    sink.byte(0);

    sink.byte(8);
    sink.blocks(compress(indices, 8));

    onProgress?.((f + 1) / frames.length);
    await new Promise((resolve) => setTimeout(resolve, 0));
  }

  sink.byte(0x3b);
  return sink.toBytes();
}