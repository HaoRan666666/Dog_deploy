#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to roboparty_imu__msg__IMUData

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct IMUData {

    // This member is not documented.
    #[allow(missing_docs)]
    pub device_id: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub accel_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub accel_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub accel_z: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gyro_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gyro_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gyro_z: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub roll: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pitch: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub q_w: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub q_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub q_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub q_z: f32,

}



impl Default for IMUData {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::IMUData::default())
  }
}

impl rosidl_runtime_rs::Message for IMUData {
  type RmwMsg = super::msg::rmw::IMUData;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        device_id: msg.device_id,
        accel_x: msg.accel_x,
        accel_y: msg.accel_y,
        accel_z: msg.accel_z,
        gyro_x: msg.gyro_x,
        gyro_y: msg.gyro_y,
        gyro_z: msg.gyro_z,
        roll: msg.roll,
        pitch: msg.pitch,
        yaw: msg.yaw,
        q_w: msg.q_w,
        q_x: msg.q_x,
        q_y: msg.q_y,
        q_z: msg.q_z,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      device_id: msg.device_id,
      accel_x: msg.accel_x,
      accel_y: msg.accel_y,
      accel_z: msg.accel_z,
      gyro_x: msg.gyro_x,
      gyro_y: msg.gyro_y,
      gyro_z: msg.gyro_z,
      roll: msg.roll,
      pitch: msg.pitch,
      yaw: msg.yaw,
      q_w: msg.q_w,
      q_x: msg.q_x,
      q_y: msg.q_y,
      q_z: msg.q_z,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      device_id: msg.device_id,
      accel_x: msg.accel_x,
      accel_y: msg.accel_y,
      accel_z: msg.accel_z,
      gyro_x: msg.gyro_x,
      gyro_y: msg.gyro_y,
      gyro_z: msg.gyro_z,
      roll: msg.roll,
      pitch: msg.pitch,
      yaw: msg.yaw,
      q_w: msg.q_w,
      q_x: msg.q_x,
      q_y: msg.q_y,
      q_z: msg.q_z,
    }
  }
}


