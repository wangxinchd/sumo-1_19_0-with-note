#!/usr/bin/env python
# Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.dev/sumo
# Copyright (C) 2009-2023 German Aerospace Center (DLR) and others.
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# https://www.eclipse.org/legal/epl-2.0/
# This Source Code may also be made available under the following Secondary
# Licenses when the conditions for such availability set forth in the Eclipse
# Public License 2.0 are satisfied: GNU General Public License, version 2
# or later which is available at
# https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later

# @file    test.py
# @author  Pablo Alvarez Lopez
# @date    2016-11-25

# import common functions for netedit tests
import os
import sys

testRoot = os.path.join(os.environ.get('SUMO_HOME', '.'), 'tests')
neteditTestRoot = os.path.join(
    os.environ.get('TEXTTEST_HOME', testRoot), 'netedit')
sys.path.append(neteditTestRoot)
import neteditTestFunctions as netedit  # noqa

# Open netedit
neteditProcess, referencePosition = netedit.setupAndStart(neteditTestRoot)

# recompute
netedit.rebuildNetwork()

# toggle select lanes
netedit.changeEditMode(netedit.attrs.modes.network.selectLane)

# go to inspect mode
netedit.inspectMode()

# inspect edge
netedit.leftClick(referencePosition, 400, 165)

# Change parameter 0 with a non valid value (empty speed)
netedit.modifyAttribute(netedit.attrs.lane.inspect.speed, "", False)

# Change parameter 0 with a non valid value (dummy speed)
netedit.modifyAttribute(netedit.attrs.lane.inspect.speed, "dummySpeed", False)

# Change parameter 0 with a non valid value (negative speed)
netedit.modifyAttribute(netedit.attrs.lane.inspect.speed, "-13", False)

# Change parameter 0 with a valid value
netedit.modifyAttribute(netedit.attrs.lane.inspect.speed, "120.5", False)

# recompute
netedit.rebuildNetwork()

# Check undo
netedit.undo(referencePosition, 1)

# recompute
netedit.rebuildNetwork()

# Check redo
netedit.redo(referencePosition, 1)

# save Netedit config
netedit.saveNeteditConfig(referencePosition)

# quit netedit
netedit.quit(neteditProcess)