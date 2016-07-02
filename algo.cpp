/*
 *
 * This file is part of the framework test program.
 *
 * Copyright(c) 2011 Miguel Colom.
 * http://mcolom.info
 *
 * This file may be licensed under the terms of of the
 * GNU General Public License Version 2 (the ``GPL'').
 *
 * Software distributed under the License is distributed
 * on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied. See the GPL for the specific language
 * governing rights and limitations.
 *
 * You should have received a copy of the GPL along with this
 * program. If not, go to http://www.gnu.org/licenses/gpl.html
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>
#ifdef _OPENMP
#include <omp.h>
#endif
//
#include "framework/CFramework.h"
#include "framework/CImage.h"
#include "framework/libparser.h"


//! Add uniform noise algorithm.
/*!
  \param *framework Framework
  \param argc Number of arguments of the program
  \param **argv Arguments of the program
*/
void algorithm(int argc, char **argv) {
  printf("Image Processing Framework minimal test\n");
  printf("Under license GNU GPL by Miguel Colom, 2011\n");
  printf("http://mcolom.info\n");
  printf("\n");
  
  CFramework *fw = CFramework::get_framework();
  fw->set_verbose(true);

  // Load input image
  CImage input;
  
  printf("Loading input image... ");
  input.load((char*)"traffic.png");
  printf("done\n");
  
  printf("Size: %dx%d\n", input.get_width(), input.get_height());
  printf("Bits per channel: %d\n", input.get_bits_per_channel());
  printf("Number of channels: %d\n", input.get_num_channels());

  // Create output
  CImage *output = new CImage(input.get_width(), input.get_height(),
                              input.get_bits_per_channel(),
                              input.get_num_channels());

  int N = input.get_width() * input.get_height();
  
  if (input.get_num_channels() == 3) {
    // Swap the first two channels
    memcpy(output->get_channel(0), input.get_channel(1), N*sizeof(float));
    memcpy(output->get_channel(1), input.get_channel(0), N*sizeof(float));
    memcpy(output->get_channel(2), input.get_channel(2), N*sizeof(float));
  }
  else
    memcpy(output->get_channel(0), input.get_channel(0), N*sizeof(float));

  // Save output
  output->save((char*)"output.png", input.get_bits_per_channel());
  delete output;
}
