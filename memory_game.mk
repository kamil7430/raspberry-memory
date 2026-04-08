################################################################################
#
# memory_game
#
################################################################################

MEMORY_GAME_VERSION = 1.1
MEMORY_GAME_SOURCE = memory_game_src.tar
MEMORY_GAME_SITE = $(TOPDIR)/package/memory_game
MEMORY_GAME_SITE_METHOD = local
MEMORY_GAME_LICENSE = Proprietary
MEMORY_GAME_DEPENDENCIES = c-periphery

$(eval $(cmake-package))
