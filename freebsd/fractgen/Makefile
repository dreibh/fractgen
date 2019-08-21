# Created by: Thomas Dreibholz <dreibh@iem.uni-due.de>
# $FreeBSD: head/graphics/fractgen/Makefile 509423 2019-08-20 11:48:20Z rodrigo $

PORTNAME=	fractgen
PORTVERSION=	2.1.7
CATEGORIES=	graphics
MASTER_SITES=	https://www.uni-due.de/~be0001/fractalgenerator/download/

MAINTAINER=	dreibh@iem.uni-due.de
COMMENT=	Fractal Generator

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		tar:xz cmake qt:5
USE_QT=		core xml widgets printsupport buildtools_build qmake_build

CMAKE_ARGS+=	-DCMAKE_INSTALL_MANDIR=${PREFIX}/man

.include <bsd.port.mk>
