/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */
/*
 * GStreamer
 * Copyright (C) 2012 Nicolas Bouillot <http://www.nicolasbouillot.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the names of the Centre for
 * Digital Music; Queen Mary, University of London; and Chris Cannam
 * shall not be used in advertising or otherwise to promote the sale,
 * use or other dealings in this Software without prior written
 * authorization.
 */

#ifndef __GST_VAMP_HOST__
#define __GST_VAMP_HOST__

#include <vamp-hostsdk/PluginHostAdapter.h>
#include <vamp-hostsdk/PluginInputDomainAdapter.h>
#include <vamp-hostsdk/PluginLoader.h>

#include <iostream>
#include <fstream>
#include <set>
#include <sndfile.h>

#include <cstring>
#include <cstdlib>

#include "system.h"

#include <cmath>

using namespace std;

using Vamp::Plugin;
using Vamp::PluginHostAdapter;
using Vamp::RealTime;
using Vamp::HostExt::PluginLoader;
using Vamp::HostExt::PluginWrapper;
using Vamp::HostExt::PluginInputDomainAdapter;

#define HOST_VERSION "1.5"

enum Verbosity {
    PluginIds,
    PluginOutputIds,
    PluginInformation,
    PluginInformationDetailed
};

void printFeatures(int, int, int, Plugin::FeatureSet, ofstream *, bool frames);
void transformInput(float *, size_t);
void fft(unsigned int, bool, double *, double *, double *, double *);
void printPluginPath(bool verbose);
void printPluginCategoryList();
void enumeratePlugins(Verbosity);
void listPluginsInLibrary(string soname);
int runPlugin(string myname, string soname, string id, string output,
              int outputNo, string inputFile, string outfilename, bool frames);

#endif  /* __GST_VAMP_HOST__ */
