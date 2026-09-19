# include "../includes/Point.hpp"

Fixed	vectorProduct( Point const& a, Point const& b, Point const& p )
{
	return Fixed( ( b.getX().toFloat() - a.getX().toFloat() ) * ( p.getY().toFloat() - a.getY().toFloat() ) -
				 ( b.getY().toFloat() - a.getY().toFloat() ) * ( p.getX().toFloat() - a.getX().toFloat() ) );
}

bool	isZero( Fixed value, float epsilon = 0.0001f )
{
	return ( value.toFloat() > -epsilon && value.toFloat() < epsilon );
}

bool	bsp( Point const a, Point const b, Point const c, Point const point )
{
	Fixed	vp1 = vectorProduct( a, b, point );
	Fixed	vp2 = vectorProduct( b, c, point );
	Fixed	vp3 = vectorProduct( c, a, point );

	bool	has_neg = ( vp1 < Fixed( 0 )) || ( vp2 < Fixed( 0 )) || ( vp3 < Fixed( 0 ));
	bool	has_pos = ( vp1 > Fixed( 0 )) || ( vp2 > Fixed( 0 )) || ( vp3 > Fixed( 0 ));

	if ( isZero( vp1 ) || isZero( vp2 ) || isZero( vp3 ) )
		return ( false );

	return !( has_neg && has_pos );
}