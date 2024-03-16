/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.dev/sumo
// Copyright (C) 2016-2023 German Aerospace Center (DLR) and others.
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
/// @file    GNEWalk.h
/// @author  Pablo Alvarez Lopez
/// @date    Jun 2019
///
// A class for visualizing walks in Netedit
/****************************************************************************/
#pragma once
#include <config.h>
#include <utils/gui/globjects/GUIGLObjectPopupMenu.h>

#include "GNEDemandElement.h"
#include "GNEDemandElementPlan.h"

// ===========================================================================
// class declarations
// ===========================================================================

class GNEEdge;
class GNEConnection;
class GNEVehicle;

// ===========================================================================
// class definitions
// ===========================================================================

class GNEWalk : public GNEDemandElement, public Parameterised, public GNEDemandElementPlan {

public:
    /**@brief general constructor for walks
     * @param[in] net Network in which this walk is placed
     * @param[in] personParent person parent
     * @param[in] fromEdge from edge
     * @param[in] fromTAZ from TAZ
     * @param[in] fromJunction from Junction
     * @param[in] fromBusStop from busStop
     * @param[in] fromTrainStop from trainStop
     * @param[in] toEdge to edge
     * @param[in] toTAZ to TAZ
     * @param[in] toJunction to Junction
     * @param[in] toBusStop to busStop
     * @param[in] toTrainStop to trainStop
     * @param[in] edgeList list of edges
     * @param[in] route route
     * @param[in] arrivalPosition arrival position on the destination edge
     */
    static GNEWalk* buildWalk(GNENet* net, GNEDemandElement* personParent,
                              GNEEdge* fromEdge, GNEAdditional* fromTAZ, GNEJunction* fromJunction, GNEAdditional* fromBusStop, GNEAdditional* fromTrainStop,
                              GNEEdge* toEdge, GNEAdditional* toTAZ, GNEJunction* toJunction, GNEAdditional* toBusStop, GNEAdditional* toTrainStop,
                              std::vector<GNEEdge*> edgeList, GNEDemandElement* route, double arrivalPosition);

    /// @brief default constructor
    GNEWalk(SumoXMLTag tag, GNENet* net);

    /// @brief destructor
    ~GNEWalk();

    /**@brief get move operation
     * @note returned GNEMoveOperation can be nullptr
     */
    GNEMoveOperation* getMoveOperation();

    /**@brief write demand element element into a xml file
     * @param[in] device device in which write parameters of demand element element
     */
    void writeDemandElement(OutputDevice& device) const;

    /// @brief check if current demand element is valid to be written into XML (by default true, can be reimplemented in children)
    Problem isDemandElementValid() const;

    /// @brief return a string with the current demand element problem (by default empty, can be reimplemented in children)
    std::string getDemandElementProblem() const;

    /// @brief fix demand element problem (by default throw an exception, has to be reimplemented in children)
    void fixDemandElementProblem();

    /// @name members and functions relative to elements common to all demand elements
    /// @{
    /// @brief obtain VClass related with this demand element
    SUMOVehicleClass getVClass() const;

    /// @brief get color
    const RGBColor& getColor() const;

    /// @}

    /// @name Functions related with geometry of element
    /// @{
    /// @brief update pre-computed geometry information
    void updateGeometry();

    /// @brief Returns position of additional in view
    Position getPositionInView() const;
    /// @}

    /// @name inherited from GUIGlObject
    /// @{

    /**@brief Returns an own popup-menu
     *
     * @param[in] app The application needed to build the popup-menu
     * @param[in] parent The parent window needed to build the popup-menu
     * @return The built popup-menu
     * @see GUIGlObject::getPopUpMenu
     */
    GUIGLObjectPopupMenu* getPopUpMenu(GUIMainWindow& app, GUISUMOAbstractView& parent);

    /**@brief Returns the name of the parent object
     * @return This object's parent id
     */
    std::string getParentName() const;

    /**@brief Returns the boundary to which the view shall be centered in order to show the object
     * @return The boundary the object is within
     */
    Boundary getCenteringBoundary() const;

    /// @brief split geometry
    void splitEdgeGeometry(const double splitPosition, const GNENetworkElement* originalElement, const GNENetworkElement* newElement, GNEUndoList* undoList);

    /**@brief Draws the object
     * @param[in] s The settings for the current view (may influence drawing)
     * @see GUIGlObject::drawGL
     */
    void drawGL(const GUIVisualizationSettings& s) const;

    /// @}

    /// @name inherited from GNEPathManager::PathElement
    /// @{

    /// @brief compute pathElement
    void computePathElement();

    /**@brief Draws partial object over lane
     * @param[in] s The settings for the current view (may influence drawing)
     * @param[in] segment lane segment
     * @param[in] offsetFront front offset
     */
    void drawLanePartialGL(const GUIVisualizationSettings& s, const GNEPathManager::Segment* segment, const double offsetFront) const;

    /**@brief Draws partial object over junction
     * @param[in] s The settings for the current view (may influence drawing)
     * @param[in] segment junction segment
     * @param[in] offsetFront front offset
     */
    void drawJunctionPartialGL(const GUIVisualizationSettings& s, const GNEPathManager::Segment* segment, const double offsetFront) const;

    /// @brief get first path lane
    GNELane* getFirstPathLane() const;

    /// @brief get last path lane
    GNELane* getLastPathLane() const;
    /// @}

    /// @brief inherited from GNEAttributeCarrier
    /// @{
    /* @brief method for getting the Attribute of an XML key
     * @param[in] key The attribute key
     * @return string with the value associated to key
     */
    std::string getAttribute(SumoXMLAttr key) const;

    /* @brief method for getting the Attribute of an XML key in double format (to avoid unnecessary parse<double>(...) for certain attributes)
     * @param[in] key The attribute key
     * @return double with the value associated to key
     */
    double getAttributeDouble(SumoXMLAttr key) const;

    /* @brief method for getting the Attribute of an XML key in Position format (used in person plans)
     * @param[in] key The attribute key
     * @return double with the value associated to key
     */
    Position getAttributePosition(SumoXMLAttr key) const;

    /* @brief method for setting the attribute and letting the object perform additional changes
     * @param[in] key The attribute key
     * @param[in] value The new value
     * @param[in] undoList The undoList on which to register changes
     * @param[in] net optionally the GNENet to inform about gui updates
     */
    void setAttribute(SumoXMLAttr key, const std::string& value, GNEUndoList* undoList);

    /* @brief method for setting the attribute and letting the object perform additional changes
     * @param[in] key The attribute key
     * @param[in] value The new value
     * @param[in] undoList The undoList on which to register changes
     */
    bool isValid(SumoXMLAttr key, const std::string& value);

    /* @brief method for check if the value for certain attribute is set
     * @param[in] key The attribute key
     */
    bool isAttributeEnabled(SumoXMLAttr key) const;

    /// @brief get PopPup ID (Used in AC Hierarchy)
    std::string getPopUpID() const;

    /// @brief get Hierarchy Name (Used in AC Hierarchy)
    std::string getHierarchyName() const;
    /// @}

    /// @brief get parameters map
    const Parameterised::Map& getACParametersMap() const;

private:
    /// @brief method for setting the attribute and nothing else
    void setAttribute(SumoXMLAttr key, const std::string& value);

    /// @brief set move shape
    void setMoveShape(const GNEMoveResult& moveResult);

    /// @brief commit move shape
    void commitMoveShape(const GNEMoveResult& moveResult, GNEUndoList* undoList);

    /**@brief constructor called in buildWalk
     * @param[in] net Network in which this Walk is placed
     * @param[in] tag walk tag
     * @param[in] icon walk icon
     * @param[in] parents demand element parents (person and, optionally, route)
     * @param[in] junction from-to junctions
     * @param[in] eges from-to edges
     * @param[in] additionals from-to additionals
     */
    GNEWalk(GNENet* net, SumoXMLTag tag, GUIIcon icon, std::vector<GNEDemandElement*>& parents, const std::vector<GNEJunction*>& junctions,
            const std::vector<GNEEdge*>& edges, const std::vector<GNEAdditional*>& additionals, double arrivalPosition);

    /// @brief Invalidated copy constructor.
    GNEWalk(GNEWalk*) = delete;

    /// @brief Invalidated assignment operator.
    GNEWalk& operator=(GNEWalk*) = delete;
};
