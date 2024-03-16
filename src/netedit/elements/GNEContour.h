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
/// @file    GNEContour.h
/// @author  Pablo Alvarez Lopez
/// @date    Aug 2023
///
// class used for show contour elements
/****************************************************************************/
#pragma once
#include <config.h>

#include <utils/gui/div/GUIDottedGeometry.h>

// ===========================================================================
// class declaration
// ===========================================================================

class GNENet;
class GNEEdge;
class GNEAttributeCarrier;

// ===========================================================================
// class definitions
// ===========================================================================

class GNEContour {

public:
    /// @brief Constructor
    GNEContour(GNEAttributeCarrier* AC);

    /// @brief destructor
    ~GNEContour();

    /// @brief reset dotted contour
    void reset();

    /// @brief dotted contours
    /// @{

    /// @brief draw dotted contour (for closed shapes)
    void drawDottedContourClosed(const GUIVisualizationSettings& s, const PositionVector& shape,
                                 const double scale, const bool addOffset, const double lineWidth) const;

    /// @brief draw dotted contour extruded (used in elements formed by a central shape)
    void drawDottedContourExtruded(const GUIVisualizationSettings& s, const PositionVector& shape,
                                   const double extrusionWidth, const double scale, const bool drawFirstExtrem,
                                   const bool drawLastExtrem, const double lineWidth) const;

    /// @brief draw dotted contour (for rectangled elements)
    void drawDottedContourRectangle(const GUIVisualizationSettings& s, const Position& pos, const double width,
                                    const double height, const double offsetX, const double offsetY, const double rot,
                                    const double scale, const double lineWidth) const;

    /// @brief draw dotted contour (circle)
    void drawDottedContourCircle(const GUIVisualizationSettings& s, const Position& pos, double radius,
                                 const double scale, const double lineWidth) const;

    /// @brief draw dotted contour edge
    void drawDottedContourEdge(const GUIVisualizationSettings& s, const GNEEdge* edge, const bool drawFirstExtrem,
                               const bool drawLastExtrem, const double lineWidth) const;

    /// @brief draw dotted contour between two edges
    void drawDottedContourEdges(const GUIVisualizationSettings& s, const GNEEdge* fromEdge, const GNEEdge* toEdge,
                                const double lineWidth) const;

    /// @}

    /// @brief innen contours
    /// @{

    /// @brief draw innen contour (for closed shapes)
    void drawInnenContourClosed(const GUIVisualizationSettings& s, const PositionVector& shape,
                                const double scale, const double lineWidth) const;
    /// @}

private:
    /// @brief pointer to AC
    GNEAttributeCarrier* myAC;

    /// @brief pointer to cached position
    Position* myCachedPosition;

    /// @brief pointer to cached shape
    PositionVector* myCachedShape;

    /// @brief dotted geometry color
    static GUIDottedGeometry::DottedGeometryColor myDottedGeometryColor;

    /// @brief dotted geometries
    std::vector<GUIDottedGeometry>* myDottedGeometries;

    /// @brief width, height, rot, scale
    std::vector<double>* myCachedDoubles;

    /// @brief draw dotted contour shape
    void buildAndDrawDottedContourClosed(const GUIVisualizationSettings& s, const GUIDottedGeometry::DottedContourType type,
                                         const PositionVector& shape, const double scale, const bool addOffset, const double lineWidth) const;

    /// @brief build and draw dotted contour extruded
    void buildAndDrawDottedContourExtruded(const GUIVisualizationSettings& s, GUIDottedGeometry::DottedContourType type,
                                           const PositionVector& shape, const double extrusionWidth, const double scale,
                                           const bool drawFirstExtrem, const bool drawLastExtrem, const double lineWidth) const;

    /// @brief draw dotted contour rectangle
    void buildAndDrawDottedContourRectangle(const GUIVisualizationSettings& s, GUIDottedGeometry::DottedContourType type,
                                            const Position& pos, const double width, const double height, const double offsetX,
                                            const double offsetY, const double rot, const double scale, const double lineWidth) const;

    /// @brief draw dotted contour circle
    void buildAndDrawDottedContourCircle(const GUIVisualizationSettings& s, GUIDottedGeometry::DottedContourType type,
                                         const Position& pos, double radius, const double scale, const double lineWidth) const;

    /// @brief draw dotted contour edge
    void buildAndDrawDottedContourEdge(const GUIVisualizationSettings& s, GUIDottedGeometry::DottedContourType type,
                                       const GNEEdge* edge, const bool drawFirstExtrem, const bool drawLastExtrem, const double lineWidth) const;

    /// @brief draw dotted contour edges
    void buildAndDrawDottedContourEdges(const GUIVisualizationSettings& s, GUIDottedGeometry::DottedContourType type,
                                        const GNEEdge* fromEdge, const GNEEdge* toEdge, const double lineWidth) const;

    /// @brief invalidate default constructor
    GNEContour() = delete;

    /// @brief Invalidated copy constructor.
    GNEContour(const GNEContour&) = delete;

    /// @brief Invalidated assignment operator
    GNEContour& operator=(const GNEContour& src) = delete;
};
