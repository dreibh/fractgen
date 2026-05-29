PORTNAME=	fractgen
DISTVERSION=	3.0.10
CATEGORIES=	graphics
MASTER_SITES=	https://www.nntb.no/~dreibh/fractalgenerator/download/

MAINTAINER=	thomas.dreibholz@gmail.com
COMMENT=	Fractal Generator
WWW=		https://www.nntb.no/~dreibh/fractalgenerator/

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		cmake compiler:c++23-lang desktop-file-utils gl qt:6 \
		shared-mime-info tar:xz
USE_GL=		opengl
USE_QT=		base tools:build imageformats:run

OPTIONS_DEFINE=			FRACTGEN_CLI \
				FRACTGEN_KDE \
				FRACTGEN_QT \
				EXAMPLES

OPTIONS_DEFAULT=		${OPTIONS_DEFINE}
OPTIONS_SUB=			yes

FRACTGEN_CLI_DESC=		Build the Qt version
FRACTGEN_KDE_DESC=		Build the KDE version
FRACTGEN_QT_DESC=		Build the Qt version
EXAMPLES_DESC=			Include example files

FRACTGEN_CLI_CMAKE_BOOL=	WITH_CLI

FRACTGEN_KDE_CMAKE_BOOL=	WITH_KDE

FRACTGEN_QT_CMAKE_BOOL=		WITH_QT

EXAMPLES_CMAKE_BOOL=		WITH_EXAMPLES

.include <bsd.port.mk>
