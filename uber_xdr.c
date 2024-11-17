/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "uber.h"

bool_t
xdr_Posicion (XDR *xdrs, Posicion *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->x))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->y))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_InfoAuto (XDR *xdrs, InfoAuto *objp)
{
	register int32_t *buf;

	 if (!xdr_Posicion (xdrs, &objp->posicion))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->tipoUber, 10))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->tarifa))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->placa, 10))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_EstadoServicio (XDR *xdrs, EstadoServicio *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->viajesRealizados))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->autosLibres))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->gananciaTotal))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_TerminarViajeArgs (XDR *xdrs, TerminarViajeArgs *objp)
{
	register int32_t *buf;

	 if (!xdr_Posicion (xdrs, &objp->posicionFinal))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->costoViaje))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->placas, 10))
		 return FALSE;
	return TRUE;
}
