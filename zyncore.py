#!/usr/bin/python3
# -*- coding: utf-8 -*-
# ********************************************************************
# ZYNTHIAN PROJECT: Zynthian Core library python wrapper
# 
# A Python wrapper for Zynthian Core library
# 
# Copyright (C) 2015-2021 Fernando Moyano <jofemodo@zynthian.org>
#
# ********************************************************************
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# For a full copy of the GNU General Public License see the LICENSE.txt file.
# 
# ********************************************************************

from ctypes import *
import os
from os.path import dirname, realpath
#from numpy.ctypeslib import ndpointer

# -------------------------------------------------------------------------------
# Zyncoder Library Wrapper
# -------------------------------------------------------------------------------

global lib_zyncore
lib_zyncore = None


def zyncore_lib_path():
	"""libzyncore.so from ZYNTHIAN_LIB_DIR (installed package) if it's there, else from the build directory.
	The kit's build (zyncoder-hw: ZYNTHIAN_LIB_DIR/hw/<ZYNTHIAN_WIRING_LAYOUT>/libzyncore.so, with the
	kit's wiring compiled in) comes before the generic one."""
	lib_dir = os.environ.get("ZYNTHIAN_LIB_DIR", "")
	if lib_dir:
		layout = os.environ.get("ZYNTHIAN_WIRING_LAYOUT", "")
		if layout and "/" not in layout:
			path = os.path.join(lib_dir, "hw", layout, "libzyncore.so")
			if os.path.isfile(path):
				return path
		if os.path.isfile(os.path.join(lib_dir, "libzyncore.so")):
			return os.path.join(lib_dir, "libzyncore.so")
	return dirname(realpath(__file__)) + "/build/libzyncore.so"


def lib_zyncore_init():
	global lib_zyncore
	try:
		lib_zyncore = cdll.LoadLibrary(zyncore_lib_path())
		result = lib_zyncore.init_zyncore()
	except Exception as e:
		lib_zyncore = None
		raise Exception(f"Can't init zyncore library: {e}")

	if result != 0:
		lib_zyncore = None
		if result == 1:
			raise Exception("Failed to initialise zyncontrol", 1)
		elif result == 2:
			raise Exception("Failed to initialise zynmidirouter", 2)
		elif result == 3:
			raise Exception("Failed to initialise zynmaster_jack", 3)

	# Setup return type for some functions
	#lib_zyncore.get_midi_filter_clone_cc.restype = ndpointer(dtype=c_ubyte, shape=(128,))

	#raise Exception("Failed to initialise zyncontrol", 1)
	#raise Exception("Failed to initialise zynmidirouter", 2)
	return lib_zyncore


def lib_zyncore_init_minimal():
	global lib_zyncore
	try:
		lib_zyncore = cdll.LoadLibrary(zyncore_lib_path())
		lib_zyncore.init_zyncore_minimal()

	except Exception as e:
		lib_zyncore = None
		print("Can't init minimal zyncore library: %s" % str(e))

	return lib_zyncore


def get_lib_zyncore():
	return lib_zyncore

# -------------------------------------------------------------------------------
