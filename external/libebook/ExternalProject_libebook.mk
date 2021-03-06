# -*- Mode: makefile-gmake; tab-width: 4; indent-tabs-mode: t -*-
#
# This file is part of the LibreOffice project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

$(eval $(call gb_ExternalProject_ExternalProject,libebook))

$(eval $(call gb_ExternalProject_use_autoconf,libebook,build))

$(eval $(call gb_ExternalProject_register_targets,libebook,\
	build \
))

$(eval $(call gb_ExternalProject_use_externals,libebook,\
	boost_headers \
	icu \
	libxml2 \
	wpd \
	zlib \
))

$(call gb_ExternalProject_get_state_target,libebook,build) :
	$(call gb_ExternalProject_run,build,\
		export PKG_CONFIG="" \
		&& ./configure \
			--with-pic \
			--enable-static \
			--disable-shared \
			--without-docs \
			$(if $(filter TRUE,$(ENABLE_DEBUG)),--enable-debug,--disable-debug) \
			--disable-werror \
			--disable-weffc \
			CXXFLAGS="$(if $(SYSTEM_BOOST),$(BOOST_CPPFLAGS),-I$(call gb_UnpackedTarball_get_dir,boost) -I$(BUILDDIR)/config_$(gb_Side))" \
			XML_CFLAGS="$(if $(SYSTEM_LIBXML),$(LIBXML_CFLAGS),-I$(call gb_UnpackedTarball_get_dir,xml2)/include)" \
			XML_LIBS="$(LIBXML_LIBS)" \
			$(if $(CROSS_COMPILING),--build=$(BUILD_PLATFORM) --host=$(HOST_PLATFORM)) \
		&& cd src/lib \
		&& $(MAKE) $(if $(VERBOSE)$(verbose),V=1) \
	)

# vim: set noet sw=4 ts=4:
