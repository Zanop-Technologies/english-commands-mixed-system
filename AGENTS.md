# Agent guidance
## Project context
- ECMXS is an English Commands Mixed Set shell; command reference is in `COMMANDLIST.md`.
- C++ source and headers belong under `src/`.
- `frt` means **Fart**, not Fast Route Test. The command reference describes `frt -i -p <packets> <ip>` as a ping-like command.

## Implementation notes
- Keep parsing, command results, and individual command behavior in focused C++ files under `src/`.
- Use the `ecmxs` namespace for shared implementation types.
- Do not claim platform-level networking behavior unless it is actually implemented.
