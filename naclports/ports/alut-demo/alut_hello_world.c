#include <stdlib.h>
#include <stdio.h>
#include <AL/alut.h>

#include <ppapi/c/ppb.h>
#include <ppapi_simple/ps.h>

/*
  This is the 'Hello World' program from the ALUT
  reference manual.

  Link using '-lalut -lopenal -lpthread'.
*/

void alSetPpapiInfo(PP_Instance instance, PPB_GetInterface get_interface);

int main(int argc, char** argv) {
  ALuint helloBuffer, helloSource;

  /*
   * This extra line is required by the underlying openAl
   * NaCl port.
   */
  alSetPpapiInfo(PSGetInstanceId(), PSGetInterface);

  alutInit(&argc, argv);
  helloBuffer = alutCreateBufferHelloWorld();
  alGenSources(1, &helloSource);
  alSourcei(helloSource, AL_BUFFER, helloBuffer);
  alSourcePlay(helloSource);
  alutSleep(1);
  alutExit();
  return EXIT_SUCCESS;
}
