# Created by: Thomas Dreibholz <thomas.dreibholz@gmail.com>
# $FreeBSD: head/graphics/fractgen/Makefile 509941 2019-08-26 12:59:18Z pkubaj $

PORTNAME=	fractgen
PORTVERSION=	2.1.14~rc1
CATEGORIES=	graphics
MASTER_SITES=	https://www.nntb.no/~dreibh/fractalgenerator/download/

MAINTAINER=	thomas.dreibholz@gmail.com
COMMENT=	Fractal Generator

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		compiler:c++11-lang tar:xz cmake qt:5
USE_QT=		core xml widgets printsupport linguisttools buildtools_build buildtools_build qmake_build

CMAKE_ARGS+=	-DCMAKE_INSTALL_MANDIR=${PREFIX}/man

.include <bsd.port.mk>
