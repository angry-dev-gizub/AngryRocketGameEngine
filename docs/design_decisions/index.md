# Angry Rocket – Design Decisions

This directory contains the architectural and technical design decisions made during the development of Angry Rocket Engine.

Each dated directory contains individual decision documents and an index listing the decisions made on that date.

## Decisions by Date

| Date | Description | Index |
|---|---|---|
| 24-11-2026 | Initial architecture, PAL, filesystem, allocators and error handling | [Open](24-11-2026/index.md) |
| 26-11-2026 | Core architecture integration and error system redesign | [Open](26-11-2026/index.md) |

## Directory Structure

```text
design_decisions/
├── index.md
├── 24-11-2026/
│   ├── index.md
│   ├── DD-001.md
│   └── ...
└── 26-11-2026/
    ├── index.md
    ├── DD-001.md
    └── ...
```

## Status Definitions

| Status | Meaning |
|---|---|
| Proposed | Decision is being discussed and has not been finalized. |
| Accepted | Decision has been agreed upon. |
| Superseded | Decision has been replaced by a newer decision. |
| Deprecated | Decision is no longer recommended but has not necessarily been replaced. |

## Conventions

- Each date has its own directory using the `DD-MM-YYYY` format.
- Decision numbering starts at `DD-001` for each date.
- Each decision is documented in an individual Markdown file.
- Each dated directory contains an `index.md` linking to its decisions.
- Individual decisions include navigation links to the previous decision, the date index, and the next decision where applicable.
- Decisions are preserved even when superseded, maintaining the project's architectural history.