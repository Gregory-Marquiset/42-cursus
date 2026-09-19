# Portail web de 42-cursus : la page du graph (nginx) et un terminal web (ttyd) qui execute ./cursus.
# Le conteneur pilote le Docker de la machine par son socket.
FROM alpine:3.20

RUN apk add --no-cache bash coreutils sed grep docker-cli docker-cli-compose ttyd nginx

COPY nginx.conf /etc/nginx/http.d/default.conf
COPY start.sh /start.sh

EXPOSE 4242
CMD ["sh", "/start.sh"]
