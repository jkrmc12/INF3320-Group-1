/* $Id: oblig2.cpp, v1.1 2008/09/22$
 *
 * Author: Atgeirr F Rasmussen <atgeirr@sintef.no>
 *
 * Distributed under the GNU GPL.
 */

#include "GLUTWrapper.hpp"
#include "Oblig1.hpp"

int main(int argc, char** argv) {
    Oblig1 app;
    return GLUTWrapper::run(argc, argv, app);
}
