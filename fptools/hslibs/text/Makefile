# $Id: Makefile,v 1.22 2003/09/16 12:52:16 simonmar Exp $

TOP = ..
include $(TOP)/mk/boilerplate.mk

PACKAGE = text
PACKAGE_DEPS = lang data

ALL_DIRS = html parsec

SRC_HC_OPTS += -cpp -fvia-C

parsec/ParsecToken_HC_OPTS += -fglasgow-exts
parsec/ParsecPerm_HC_OPTS += -fglasgow-exts

include $(TOP)/mk/target.mk
