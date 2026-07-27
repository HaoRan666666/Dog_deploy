from setuptools import find_packages
from setuptools import setup

setup(
    name='imu_ros2',
    version='0.1.0',
    packages=find_packages(
        include=('imu_ros2', 'imu_ros2.*')),
)
