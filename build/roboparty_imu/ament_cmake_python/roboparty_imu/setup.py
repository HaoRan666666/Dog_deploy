from setuptools import find_packages
from setuptools import setup

setup(
    name='roboparty_imu',
    version='0.1.0',
    packages=find_packages(
        include=('roboparty_imu', 'roboparty_imu.*')),
)
