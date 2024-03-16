/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.dev/sumo
// Copyright (C) 2001-2023 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    GUIDottedGeometry.cpp
/// @author  Pablo Alvarez Lopez
/// @date    Oct 2021
///
// File for dotted geometry classes and functions
/****************************************************************************/
#include <utils/geom/GeomHelper.h>
#include <utils/gui/div/GLHelper.h>
#include <utils/gui/globjects/GLIncludes.h>
#include <utils/gui/globjects/GUIGlObjectTypes.h>

#include "GUIDottedGeometry.h"
#include "GUIGeometry.h"


#define MAXIMUM_DOTTEDGEOMETRYLENGTH 500.0

// ===========================================================================
// method definitions
// ===========================================================================

// ---------------------------------------------------------------------------
// GUIDottedGeometry::DottedGeometryColor - methods
// ---------------------------------------------------------------------------

GUIDottedGeometry::DottedGeometryColor::DottedGeometryColor() :
    myColorFlag(true) {}


const RGBColor
GUIDottedGeometry::DottedGeometryColor::getColor(const GUIVisualizationSettings& settings, DottedContourType type) {
    switch (type) {
        case DottedContourType::INSPECT:
            if (myColorFlag) {
                myColorFlag = false;
                return settings.dottedContourSettings.firstInspectedColor;
            } else {
                myColorFlag = true;
                return settings.dottedContourSettings.secondInspectedColor;
            }
        case DottedContourType::FRONT:
            if (myColorFlag) {
                myColorFlag = false;
                return settings.dottedContourSettings.firstFrontColor;
            } else {
                myColorFlag = true;
                return settings.dottedContourSettings.secondFrontColor;
            }
        case DottedContourType::FROM:
            if (myColorFlag) {
                myColorFlag = false;
                return RGBColor::GREEN;
            } else {
                myColorFlag = true;
                return RGBColor::GREEN.changedBrightness(-30);
            }
        case DottedContourType::TO:
            if (myColorFlag) {
                myColorFlag = false;
                return RGBColor::MAGENTA;
            } else {
                myColorFlag = true;
                return RGBColor::MAGENTA.changedBrightness(-30);
            }
        case DottedContourType::REMOVE:
            if (myColorFlag) {
                myColorFlag = false;
                return RGBColor(229, 233, 255);
            } else {
                myColorFlag = true;
                return RGBColor(255, 109, 196);
            }
        case DottedContourType::SELECT:
            if (myColorFlag) {
                myColorFlag = false;
                return RGBColor::BLUE;
            } else {
                myColorFlag = true;
                return RGBColor::BLUE.changedBrightness(-30);
            }
        case DottedContourType::OVER:
            if (myColorFlag) {
                myColorFlag = false;
                return RGBColor::ORANGE;
            } else {
                myColorFlag = true;
                return RGBColor::ORANGE.changedBrightness(-30);
            }
        case DottedContourType::RELATED:
            if (myColorFlag) {
                myColorFlag = false;
                return RGBColor::CYAN;
            } else {
                myColorFlag = true;
                return RGBColor::CYAN.changedBrightness(-30);
            }
        default:
            return RGBColor::BLACK;
    }
}


void
GUIDottedGeometry::DottedGeometryColor::changeColor() {
    if (myColorFlag) {
        myColorFlag = false;
    } else {
        myColorFlag = true;
    }
}


void
GUIDottedGeometry::DottedGeometryColor::reset() {
    myColorFlag = true;
}

// ---------------------------------------------------------------------------
// GUIDottedGeometry::Segment - methods
// ---------------------------------------------------------------------------

GUIDottedGeometry::Segment::Segment() {}


GUIDottedGeometry::Segment::Segment(PositionVector newShape) :
    shape(newShape) {
}

// ---------------------------------------------------------------------------
// GUIDottedGeometry - methods
// ---------------------------------------------------------------------------

GUIDottedGeometry::GUIDottedGeometry() {}


GUIDottedGeometry::GUIDottedGeometry(const GUIVisualizationSettings& s, PositionVector shape,
                                     const bool closeShape, const bool resample) {
    // check if shape has to be closed
    if (closeShape && (shape.size() > 2)) {
        shape.closePolygon();
    }
    if (shape.size() > 1) {
        // get shape
        for (int i = 1; i < (int)shape.size(); i++) {
            myDottedGeometrySegments.push_back(Segment({shape[i - 1], shape[i]}));
        }
        // calculate segment length
        double segmentLength = s.dottedContourSettings.segmentLength;
        if (shape.length2D() > MAXIMUM_DOTTEDGEOMETRYLENGTH) {
            segmentLength = shape.length2D() / (MAXIMUM_DOTTEDGEOMETRYLENGTH * 0.5);
        }
        // check if resample
        if (resample) {
            for (auto& segment : myDottedGeometrySegments) {
                segment.shape = segment.shape.resample(segmentLength, true);
            }
        }
        // calculate shape rotations and lengths
        calculateShapeRotationsAndLengths();
    }
}


void
GUIDottedGeometry::updateDottedGeometry(const GUIVisualizationSettings& s, const PositionVector& laneShape,
                                        const bool resample) {
    // reset segments
    myDottedGeometrySegments.clear();
    // get shape
    for (int i = 1; i < (int)laneShape.size(); i++) {
        myDottedGeometrySegments.push_back(Segment({laneShape[i - 1], laneShape[i]}));
    }
    // check if resample
    if (resample) {
        for (auto& segment : myDottedGeometrySegments) {
            segment.shape = segment.shape.resample(s.dottedContourSettings.segmentLength, true);
        }
    }
    // calculate shape rotations and lengths
    calculateShapeRotationsAndLengths();
}


void
GUIDottedGeometry::updateDottedGeometry(const GUIVisualizationSettings& s, PositionVector shape, const bool closeShape,
                                        const bool resample) {
    // reset segments
    myDottedGeometrySegments.clear();
    // check if shape has to be closed
    if (closeShape && (shape.size() > 2)) {
        shape.closePolygon();
    }
    if (shape.size() > 1) {
        // get shape
        for (int i = 1; i < (int)shape.size(); i++) {
            myDottedGeometrySegments.push_back(Segment({shape[i - 1], shape[i]}));
        }
        // check if resample
        if (resample) {
            for (auto& segment : myDottedGeometrySegments) {
                segment.shape = segment.shape.resample(s.dottedContourSettings.segmentLength, true);
            }
        }
        // calculate shape rotations and lengths
        calculateShapeRotationsAndLengths();
    }
}


void
GUIDottedGeometry::drawDottedGeometry(const GUIVisualizationSettings& s, GUIDottedGeometry::DottedContourType type,
                                      DottedGeometryColor& dottedGeometryColor, const bool addOffset, const double lineWidth) const {
    // iterate over all segments
    for (auto& segment : myDottedGeometrySegments) {
        // iterate over shape
        for (int i = 0; i < ((int)segment.shape.size() - 1); i++) {
            // set color
            GLHelper::setColor(dottedGeometryColor.getColor(s, type));
            // draw box line depending of addOffset
            if (addOffset) {
                GLHelper::drawBoxLine(segment.shape[i], segment.rotations.at(i), segment.lengths.at(i), lineWidth, -lineWidth);
            } else {
                GLHelper::drawBoxLine(segment.shape[i], segment.rotations.at(i), segment.lengths.at(i), lineWidth);
            }
        }
    }
}


void
GUIDottedGeometry::drawInnenGeometry(const double lineWidth) const {
    // iterate over all segments
    for (auto& segment : myDottedGeometrySegments) {
        // iterate over shape
        for (int i = 0; i < ((int)segment.shape.size() - 1); i++) {
            GLHelper::drawBoxLine(segment.shape[i], segment.rotations.at(i), segment.lengths.at(i), lineWidth, lineWidth);
        }
    }
}


void
GUIDottedGeometry::moveShapeToSide(const double value) {
    // move 2 side
    for (auto& segment : myDottedGeometrySegments) {
        segment.shape.move2side(value);
    }
}


Position
GUIDottedGeometry::getFrontPosition() const {
    if (myDottedGeometrySegments.size() > 0 && myDottedGeometrySegments.front().shape.size() > 0) {
        return myDottedGeometrySegments.front().shape.front();
    } else {
        return Position::INVALID;
    }
}


Position
GUIDottedGeometry::getBackPosition() const {
    if (myDottedGeometrySegments.size() > 0 && myDottedGeometrySegments.back().shape.size() > 0) {
        return myDottedGeometrySegments.back().shape.back();
    } else {
        return Position::INVALID;
    }
}


void
GUIDottedGeometry::calculateShapeRotationsAndLengths() {
    // iterate over all segments
    for (auto& segment : myDottedGeometrySegments) {
        // Get number of parts of the shape
        int numberOfSegments = (int)segment.shape.size() - 1;
        // If number of segments is more than 0
        if (numberOfSegments >= 0) {
            // Reserve memory (To improve efficiency)
            segment.rotations.reserve(numberOfSegments);
            segment.lengths.reserve(numberOfSegments);
            // Calculate lengths and rotations for every shape
            for (int i = 0; i < numberOfSegments; i++) {
                segment.rotations.push_back(GUIGeometry::calculateRotation(segment.shape[i], segment.shape[i + 1]));
                segment.lengths.push_back(GUIGeometry::calculateLength(segment.shape[i], segment.shape[i + 1]));
            }
        }
    }
}

/****************************************************************************/
