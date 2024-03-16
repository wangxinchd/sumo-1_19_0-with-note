REM Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.dev/sumo
REM Copyright (C) 2008-2023 German Aerospace Center (DLR) and others.
REM This program and the accompanying materials
REM are made available under the terms of the Eclipse Public License v2.0
REM which accompanies this distribution, and is available at
REM http://www.eclipse.org/legal/epl-v20.html
REM SPDX-License-Identifier: EPL-2.0
set TEXTTEST_HOME=%~dp0
IF "%SUMO_HOME%"=="" SET SUMO_HOME=%~dp0\..
set ACTIVITYGEN_BINARY=%SUMO_HOME%\bin\activitygen%1.exe
set DFROUTER_BINARY=%SUMO_HOME%\bin\dfrouter%1.exe
set DUAROUTER_BINARY=%SUMO_HOME%\bin\duarouter%1.exe
set JTRROUTER_BINARY=%SUMO_HOME%\bin\jtrrouter%1.exe
set NETCONVERT_BINARY=%SUMO_HOME%\bin\netconvert%1.exe
set NETEDIT_BINARY=%SUMO_HOME%\bin\netedit%1.exe
set NETGENERATE_BINARY=%SUMO_HOME%\bin\netgenerate%1.exe
set OD2TRIPS_BINARY=%SUMO_HOME%\bin\od2trips%1.exe
set SUMO_BINARY=%SUMO_HOME%\bin\sumo%1.exe
set POLYCONVERT_BINARY=%SUMO_HOME%\bin\polyconvert%1.exe
set GUISIM_BINARY=%SUMO_HOME%\bin\sumo-gui%1.exe
set MAROUTER_BINARY=%SUMO_HOME%\bin\marouter%1.exe
set EMISSIONSDRIVINGCYCLE_BINARY=%SUMO_HOME%\bin\emissionsDrivingCycle%1.exe
set EMISSIONSMAP_BINARY=%SUMO_HOME%\bin\emissionsMap%1.exe
set PYTHON=python
set LANG=C

SET TEXTTESTPY=texttest.exe
where.exe %TEXTTESTPY% > NUL 2> NUL
IF NOT ERRORLEVEL 1 GOTO :EOF
python -c "import texttestlib"
IF NOT ERRORLEVEL 1 SET TEXTTESTPY=texttest.pyw
