.. _release_notes_1.4.1:

ACRN v1.4.1 (Dec 2019)
######################

We are pleased to announce the release of ACRN version 1.4.1.

ACRN is a flexible, lightweight reference hypervisor that is built with
real-time and safety-criticality in mind. It is optimized to streamline embedded
development through an open source platform. Check out the :ref:`introduction` for more information.
All project ACRN source code is maintained in the https://github.com/projectacrn/acrn-hypervisor
repository and includes folders for the ACRN hypervisor, the ACRN device
model, tools, and documentation. You can either download this source code as
a zip or tar.gz file (see the `ACRN v1.4 GitHub release page
<https://github.com/projectacrn/acrn-hypervisor/releases/tag/v1.4>`_)
or use Git clone and checkout commands::

   git clone https://github.com/projectacrn/acrn-hypervisor
   cd acrn-hypervisor
   git checkout v1.4.1

The project's online technical documentation is also tagged to correspond
with a specific release: generated v1.4 documents can be found at https://projectacrn.github.io/1.4/.
Documentation for the latest (master) branch is found at https://projectacrn.github.io/latest/.
ACRN v1.4 requires Clear Linux* OS version 31670. Follow the
instructions in the :ref:`rt_industry_setup`.

Version 1.4.1 major features
****************************

What's New in v1.4.1
====================
* ACRN supports VM memory backed by two non-contiguous regions of Host physical memory
  for Pre-Launched VMs.
* Fix to handle "PCI-PCI Bridge" Device Scope in DMAR DRHD Device Scope Structures.

Document updates
================

Security Vulnerabilities
************************

New Features Details
********************

- :acrn-issue:`4195` - Add support to assign non-contiguous HPA regions for pre-launched VM.
- :acrn-issue:`4150` - Fix gaps in ACRN support for server platforms.

Fixed Issues Details
********************

Known Issues
************

Change Log
**********

These commits have been added to the acrn-hypervisor repo since the v1.4.1
release in Oct 2019 (click on the CommitID link to see details):

.. comment

   This list is obtained from this git command (update the date to pick up
   changes since the last release):

   git log --pretty=format:'- :acrn-commit:`%h` - %s' --after="2019-09-28"

- :acrn-commit:`c57126ed` - acrn-config: Fix ve820 table generation when guest memory size is >512MB
- :acrn-commit:`265fb56e` - acrn-config: Fix board_c.py to backport ACRN changes to 1.4
- :acrn-commit:`f3688c7e` - acrn-config: Fix target xml generation issue when no P-state scaling driver is present
- :acrn-commit:`8c87ee39` - acrn-config: by-pass acpi_idle/acpi_cpufreq for parsing target board
- :acrn-commit:`d559c3cc` - HV: Kconfig changes to support server platform.
- :acrn-commit:`e1c5bd78` - acrn-config: support non-contiguous HPA for pre-launched VM
- :acrn-commit:`fa0a6586` - HV: Add support to assign non-contiguous HPA regions for pre-launched VM
- :acrn-commit:`78b2f737` - acrn-config: refinement for library config
- :acrn-commit:`502e6023` - acrn-config: Extend ve820 generation script for sizes gt 512 MB
- :acrn-commit:`ba5105cb` - hypervisor: handle reboot from non-privileged pre-launched guests
- :acrn-commit:`31a756e7` - acrn-config: Add ramdisk tag parsing support
- :acrn-commit:`7d34aa18` - acrn-config: Add ramdisk tag to supported board/scenario xmls
- :acrn-commit:`4ea35c1b` - HV: reimplement PCI device discovery
- :acrn-commit:`f8f9a2d5` - HV: refactor device_to_dmaru
- :acrn-commit:`00be85e0` - doc: Add multiple PCI segments as known limitation for hypervisor
- :acrn-commit:`7928e21d` - HV: Cleanup PCI segment usage from VT-d interfaces
- :acrn-commit:`fe20fc14` - HV: initialize IOMMU before PCI device discovery
- :acrn-commit:`ef2d43d5` - HV: add DRHD index to pci_pdev
- :acrn-commit:`b0acad33` - HV: extra methods for extracting header fields
- :acrn-commit:`f237ca21` - HV: clean up DMAR MACROs for sample platform acpi info
- :acrn-commit:`2ba18489` - HV: move dmar info definition to board.c
- :acrn-commit:`e9a1ace1` - HV: link CONFIG_MAX_IOMMU_NUM and MAX_DRHDS to DRHD_COUNT
