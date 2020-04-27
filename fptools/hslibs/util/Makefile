# -----------------------------------------------------------------------------
# $Id: Makefile,v 1.32 2003/09/23 16:03:24 sof Exp $
#
# (c) The University of Glasgow 2002
#

TOP=..
include $(TOP)/mk/boilerplate.mk

ifneq "$(TARGETPLATFORM)" "i386-unknown-mingw32"
SUBDIRS  = cbits
endif
ALL_DIRS = check
PACKAGE      = util
PACKAGE_DEPS = lang concurrent

ifeq "$(GhcLibsWithReadline)" "YES"
PACKAGE_DEPS += readline
else
EXCLUDED_SRCS += Readline.hs
endif

SRC_HC_OPTS += -cpp

SRC_CC_OPTS += -I$(GHC_INCLUDE_DIR)

Memo_HC_OPTS += -funbox-strict-fields

ifeq "$(TARGETPLATFORM)" "i386-unknown-mingw32"
  EXCLUDED_SRCS += Select.lhs
  PACKAGE_DEPS := $(filter-out posix, $(PACKAGE_DEPS))
endif

include $(TOP)/mk/target.mk
