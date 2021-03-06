/** @brief
*  @file DJI_WayPoint.h
*  @version 3.1.7
*  @date July 1st, 2016
*
*  @brief
*  Waypoint flight API for DJI onboardSDK library
*
*  @copyright 2016 DJI. All right reserved.
*
*/

#include "DJI_Mission.h"
#include <stdexcept>

#ifndef DJI_WAYPOINT_H
#define DJI_WAYPOINT_H

namespace DJI
{
namespace onboardSDK
{

class WayPoint
{
  public:
#ifndef STATIC_MEMORY
  WayPoint(CoreAPI *ControlAPI = 0);
#else
  WayPoint(WayPointData *list, uint8_t len, CoreAPI *ControlAPI = 0);
#endif // STATIC_MEMORY
  void init(WayPointInitData *Info = 0, CallBack callback = 0, UserData userData = 0);
  MissionACK init(WayPointInitData *Info, int timer);
  void start(CallBack callback = 0, UserData userData = 0);
  MissionACK start(int timer);
  void stop(CallBack callback = 0, UserData userData = 0);
  MissionACK stop(int timer);
  //! @note true for pause, false for resume
  void pause(bool isPause, CallBack callback = 0, UserData userData = 0);
  MissionACK pause(bool isPause, int timer);
  void readInitData(CallBack callback = 0, UserData userData = 0);//! @todo implement
  void readIndexData(uint8_t index, CallBack callback = 0, UserData userData = 0); //! @todo implement
  void readIdleVelocity(CallBack callback = 0, UserData userData = 0);
  //! @todo uploadAll
  //void uploadAll(CallBack callback = 0, UserData userData = 0);
  bool uploadIndexData(WayPointData *data, CallBack callback = 0, UserData userData = 0);
  WayPointDataACK uploadIndexData(WayPointData *data, int timer);
  bool uploadIndexData(uint8_t pos, CallBack callback = 0, UserData userData = 0);
  void updateIdleVelocity(float32_t meterPreSecond, CallBack callback = 0,
      UserData userData = 0);

  void setInfo(const WayPointInitData &value);
  void setIndex(WayPointData *value, size_t pos);
  WayPointInitData getInfo() const;
  WayPointData *getIndex() const;
  WayPointData *getIndex(size_t pos) const;

  public:
  static void idleVelocityCallback(CoreAPI *api, Header *protocolHeader, UserData wpapi);
  static void readInitDataCallback(CoreAPI *api, Header *protocolHeader, UserData wpapi);
  static void uploadIndexDataCallback(CoreAPI *api, Header *protocolHeader, UserData wpapi);
  //! @todo add uploadAllCallback
  //! @todo add readIndexCallback

  private:
  CoreAPI *api;
  WayPointInitData info;
  WayPointData *index;
#ifdef STATIC_MEMORY
  uint8_t maxIndex;
#endif // STATIC_MEMORY
};

} // namespace onboardSDK
} // namespace DJI

#endif // DJI_WAYPOINT_H
