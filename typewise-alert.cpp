#include "typewise-alert.h"
#include <stdio.h>

class ClassifyTemp
{
public:
    virtual BreachType classifyTempLevel() = 0;
};

class PassiveCooling : public ClassifyTemp
{
public:
    BreachType classifyTempLevel(double temperatureInC)
    {
	return inferBreach(temperatureInC, 0, 35);
    }
};

class HiActiveCooling : public ClassifyTemp
{
public:
    BreachType classifyTempLevel(double temperatureInC)
    {
	return inferBreach(temperatureInC, 40, 45);
    }
};

class MedActiveCooling : public ClassifyTemp
{
public:
    BreachType classifyTempLevel(double temperatureInC)
    {
	return inferBreach(temperatureInC, 35, 40);
    }
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
	ClassifyTemp passive = new PassiveCooling();
	ClassifyTemp hiAcyive = new HiActiveCooling();
	ClassifyTemp medActive = new MedActiveCooling();
	passive.classifyTempLevel(temperatureInC);
	hiAcyive.classifyTempLevel(temperatureInC);
	medActive.classifyTempLevel(temperatureInC);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
