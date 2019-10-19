# MA1 General Game Programming Assignment

## Getting Started 

### Project Style Guide

- The project uses the [UE4 Project style guide](https://github.com/Allar/ue4-style-guide).
  - _All project specific assets_ should reside in the top level folder `Content/_SokobanAssignment` (see [section 2.2](https://github.com/Allar/ue4-style-guide#22-use-a-top-level-folder-for-project-specific-assets)).
  - The folders belonging to the _Third Person Template_ (`Geometry, Mannequin, ThirdPerson and ThirdPersonCPP`) are an exception for now, but should eventually become part of the top level folder or get sorted out.
  - The `Content/Developers` folder is not for assets that the project relies on and therefore is not project specific.
    - Each developer can have their own sub-folder, which is not meant to be used by others.
    - It can be made visible in the view options of the UE4 content browser.
- UE4 _starter content_ (the `Content/StarterContent` folder) is _ignored_ by the repository. **When using any starter content for the final project, move the respective files to the project folder structure** to include them in this repository.

### Version Control

To get started, clone the repository, check out _develop_ and create a new feature branch (preferably, use the git flow feature of your Git client).

- The _master_ branch should always contain a stable version and is not meant for development.
- The _development_ branch should contain the latest development version. New feature branches should be created off development.

## Troubleshooting

UE4's derived folders are not included in the repo in order to save space. When cloning the repo (or when experiencing issues when loading the project), the derived folders and the VS solution should be re-created:

1. "Check-out" or "Reset" - to a working commit
2. Delete derived folders:
   1. `Binaries`
   2. `Intermediate`
   3. `Saved` 
   4. and files: `*.sln`. 
3. **Keep** `Config`, `Content` & `Source` folders as well as `*.uproject` file (and any version control files, e.g. `*.git`).
4. Re-open Unreal - from the launcher or .uproject (_This re-creates generated.h files in Intermediate_)
5. Generate your IDE project files (Win: via Explorer right-click context menu; Mac: Via Unreal)
