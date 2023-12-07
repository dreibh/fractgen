# Created by: Thomas Dreibholz <thomas.dreibholz@gmail.com>

PORTNAME=	fractgen
PORTVERSION=	2.1.14
CATEGORIES=	graphics
MASTER_SITES=	https://www.nntb.no/~dreibh/fractalgenerator/download/

MAINTAINER=	thomas.dreibholz@gmail.com
COMMENT=	Fractal Generator
WWW=		https://www.nntb.no/~dreibh/fractalgenerator/

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		compiler:c++11-lang tar:xz cmake qt:5
USE_QT=		core xml widgets printsupport gui \
		buildtools_build qmake_build linguisttools_build

CMAKE_ARGS+=	-DCMAKE_INSTALL_MANDIR=${PREFIX}/man

.include <bsd.port.mk>
