#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "roboparty_imu__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__roboparty_imu__msg__IMUData() -> *const std::ffi::c_void;
}

#[link(name = "roboparty_imu__rosidl_generator_c")]
extern "C" {
    fn roboparty_imu__msg__IMUData__init(msg: *mut IMUData) -> bool;
    fn roboparty_imu__msg__IMUData__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<IMUData>, size: usize) -> bool;
    fn roboparty_imu__msg__IMUData__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<IMUData>);
    fn roboparty_imu__msg__IMUData__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<IMUData>, out_seq: *mut rosidl_runtime_rs::Sequence<IMUData>) -> bool;
}

// Corresponds to roboparty_imu__msg__IMUData
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !roboparty_imu__msg__IMUData__init(&mut msg as *mut _) {
        panic!("Call to roboparty_imu__msg__IMUData__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for IMUData {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { roboparty_imu__msg__IMUData__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { roboparty_imu__msg__IMUData__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { roboparty_imu__msg__IMUData__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for IMUData {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for IMUData where Self: Sized {
  const TYPE_NAME: &'static str = "roboparty_imu/msg/IMUData";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__roboparty_imu__msg__IMUData() }
  }
}


