PORTNAME=	fractgen
DISTVERSION=	3.0.2
CATEGORIES=	graphics
MASTER_SITES=	https://www.nntb.no/~dreibh/fractalgenerator/download/

MAINTAINER=	thomas.dreibholz@gmail.com
COMMENT=	Fractal Generator
WWW=		https://www.nntb.no/~dreibh/fractalgenerator/

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=  /usr/local/lib/qt6/bin/lrelease:devel/qt6-tools
LIB_DEPENDS=	libGLX.so:graphics/libglvnd

USES=		cmake compiler:c++17-lang desktop-file-utils shared-mime-info \
		tar:xz qt:6
USE_QT=		base tools
USE_GL+=	gl opengl

.include <bsd.port.mk>
