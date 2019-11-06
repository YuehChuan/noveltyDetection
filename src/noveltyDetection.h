#ifndef NOVELTY_DETECTION_H
#define NOVELT_DETECTION_H

#include <Arduino.h>
#include <EEPROM.h>
#include <SD.h>

//Used to read the right file from the SD Card
#define SVM_MODEL_FILENAME "svm.mod"
#define SVM_SCALE_PARAMETERS_FILENAME "svm.par"
//Max number of features
#define SVM_MAX_VEC_DIM 10
//Used for checking the files on SD have the correct params
#define SVM_TYPE "one_class"
#define KERNEL_TYPE "rbf"
#define NR_CLASS 2
#define SD_BUF_LENGTH 512 //newline buffer to read SVM params from SD cardshouldn't exceed 500

struct SVM_parameterStruct {
  uint32_t nVecDims;
  uint32_t totalSVs;
  float gamma;
  float rho;
};

enum eepromAddresses {
  aSVM_START, //Add stuff before this if you want to shift the SVM data forwards in the EEPROM
  aSVM_SCALE_PARAMS_START = aSVM_START + sizeof(SVM_parameterStruct),
  aSVM_SV_START = aSVM_SCALE_PARAMS_START + sizeof(float) * 2 * SVM_MAX_VEC_DIM, //sizeof float * upper+lower * 10 max vector dimensions
  aSVM_SV_END = 2000,
};

//Std scale params, these are recommended by LIBSVM
const int scalePar[] = { -1, 1};

inline float SVM_predictEEPROM(float*, uint8_t);

void SVM_scaleEEPROM(const float*, float*, uint8_t, eepromAddresses);

int SVM_readModelFromSD(const char *, const char *);

inline float SVM_rbfKernel(uint16_t, float*, uint8_t, float);

void readToCharCode(File*, char, int, char *);

const int maxSVs = (aSVM_SV_END - aSVM_SV_START) / sizeof(float);

#endif
