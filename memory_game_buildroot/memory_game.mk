################################################################################
#
# memory_game
#
################################################################################

MEMORY_GAME_VERSION = 1.0
MEMORY_GAME_SITE = $(TOPDIR)/memory_game_src
MEMORY_GAME_SITE_METHOD = local
MEMORY_GAME_LICENSE = Proprietary
MEMORY_GAME_DEPENDENCIES = periphery

$(eval $(cmake-package))
