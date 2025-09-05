# -*- coding: utf-8 -*-
"""
Multi Half-Bridge Python Library
Python package for Infineon's multi half-bridge IC drivers
"""

# Import the main module when the package is imported
try:
    from .multi_half_bridge_py import *
except ImportError:
    # Fallback for development
    try:
        import multi_half_bridge_py
        # Make all symbols available at package level
        from multi_half_bridge_py import *
    except ImportError:
        pass

__version__ = "5.0.1"
__author__ = "Infineon Technologies"
