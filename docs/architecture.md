# Angry Rocket Engine Architecture

## 1. Overview

Angry Rocket is a modular game engine designed to provide a general-purpose runtime for developing games and other interactive applications.

The engine is organized into several architectural layers. Each layer provides functionality to the layers above it while depending on the functionality provided by the layers below it.

The engine is designed around a modular plugin architecture. Engine functionality is provided through plugins that implement predefined contracts and integrate with the engine runtime.

The engine itself provides the infrastructure required to load, initialize, execute, and terminate plugins. Application-specific functionality is provided by the plugins enabled for a particular application.

The architecture is intended to support different types of applications without requiring the entire engine to be coupled to game-specific functionality.

## 2. Architectural Layers

The engine consists of the following architectural layers:

1. Operating System
2. Platform Abstraction Layer
3. Core Layer
4. Runtime Layer
5. Plugin Layer
6. Application Layer

### 2.1 Operating System

The operating system provides the underlying resources and services required by the engine.

These include, but are not limited to:

- Memory management
- File systems
- Threads and synchronization
- Dynamic library loading
- Window management
- Input devices
- Timers
- Process management

The engine does not directly depend on operating-system-specific implementations outside the Platform Abstraction Layer.

### 2.2 Platform Abstraction Layer

The Platform Abstraction Layer (PAL) provides a uniform interface for interacting with operating-system resources.

Its purpose is to abstract operating-system-specific functionality and allow the rest of the engine to operate independently of the underlying operating system.

The PAL is responsible for providing interfaces for functionality such as:

- Window creation and management
- Input handling
- File system access
- Dynamic library loading
- Threading and synchronization
- Timing
- Memory-related operating-system services
- Native dialogs
- Clipboard access

Platform-specific implementations are responsible for translating these interfaces into the appropriate operating-system functionality.

The PAL does not provide engine-specific functionality such as rendering, physics, asset processing, or application logic.

### 2.3 Core Layer

The Core Layer provides fundamental infrastructure used throughout the engine.

It is independent of higher-level engine systems and provides reusable functionality that does not require knowledge of the engine runtime or application.

Core functionality includes:

- Containers
- Arrays
- Unsorted and sorted arrays
- Hash maps
- Strings and string views
- Algorithms
- Iterators
- Generic interfaces
- Allocators
- Mathematics
- Data structures
- Utilities

The Core Layer establishes common abstractions and conventions used by the rest of the engine.

### 2.4 Runtime Layer

The Runtime Layer provides the infrastructure required to execute and manage the engine.

It is responsible for:

- Plugin management
- Plugin dependency resolution
- Plugin lifecycle management
- Runtime type information
- Object registration and management
- Object pools
- Resource management
- Asset management
- Event management
- Engine lifecycle
- Engine update loop

The Runtime Layer provides the systems required by plugins to integrate with the engine.

It does not define application-specific types, assets, events, resources, or objects. These are introduced by plugins.

### 2.5 Plugin Layer

Plugins extend the engine by providing additional functionality.

A plugin may register and provide:

- Types
- Events
- Assets
- Resources
- Objects
- Functions
- Systems
- Other plugin dependencies

Plugins integrate with the Runtime Layer through predefined contracts.

Each plugin is responsible for providing the functionality and metadata required by the runtime to manage its registered components.

Plugins may depend on other plugins. These dependencies are resolved by the runtime before plugin initialization.

### 2.6 Application Layer

The Application Layer represents the application being executed by the engine.

An application defines its configuration and the plugins required for its functionality.

Applications may use the engine to develop games, interactive applications, or other software.

The application is not required to use the Angry Rocket Native package.

---

## 3. Plugin Architecture

The engine uses a modular plugin architecture.

Plugins provide functionality through contracts defined by the Runtime Layer. The runtime manages plugin discovery, dependency resolution, initialization, execution, and termination.

### 3.1 Plugin Responsibilities

A plugin is responsible for:

- Declaring its identity and metadata.
- Declaring its dependencies.
- Registering its types.
- Registering its events.
- Registering its assets.
- Registering its resources.
- Providing object implementations.
- Providing required lifecycle callbacks.
- Providing functionality required by its registered types.

The runtime is responsible for managing these registrations and their associated lifecycles.

### 3.2 Plugin Dependencies

Plugins may depend on other plugins.

Dependencies form a directed acyclic graph (DAG).

The runtime uses a dependency resolver to determine a valid initialization order.

A plugin may only be initialized after all of its dependencies have been initialized successfully.

Plugins are terminated in reverse dependency order, ensuring that dependent plugins are terminated before the plugins they depend on.

Circular dependencies are invalid.

### 3.3 Plugin Lifecycle

Plugins follow the following lifecycle:

1. Discovery
2. Dependency resolution
3. Initialization
4. Runtime execution
5. Termination

Initialization is performed in dependency order.

Termination is performed in reverse dependency order.

A plugin that fails initialization must not be considered initialized.

The engine must handle initialization failures without leaving the runtime in an inconsistent state.

### 3.4 Plugin Contracts

Plugins interact with the runtime through predefined contracts.

These contracts define the interfaces and requirements necessary for plugin functionality to be integrated into the engine.

The runtime does not need to understand the internal implementation of a plugin. It only needs to understand the contracts exposed by the plugin.

---

## 4. Angry Rocket Native

Angry Rocket Native is the collection of plugins that provides the functionality commonly required by game applications.

It is distributed as a package containing multiple plugins.

The package is not a single plugin.

Its plugins may depend on one another and may be independently enabled or disabled according to the application configuration.

Angry Rocket Native may provide functionality such as:

- Scripting language
- Rendering
- Graphics
- Shaders
- Image decoding
- Model decoding
- Audio
- Physics (using Neptune)
- Collision detection
- Scene management
- UI utilities
- Timers
- Serialization
- Game-specific infrastructure

The exact composition of Angry Rocket Native is determined by its individual plugins.

Applications are not required to enable Angry Rocket Native.

The engine may be used with custom plugins providing alternative functionality.

---

## 5. Runtime Architecture

The Runtime Layer consists of the following primary subsystems:

1. Event System
2. Asset Manager
3. Resource Manager
4. Object RTTI System
5. Plugin Dependency Resolver

These subsystems provide the infrastructure used by the engine and its plugins.

### 5.1 Event System

The Event System provides a mechanism for communicating events between engine components and plugins.

An event consists of:

- Event type
- Event payload

The runtime provides an event type registry and an event bus.

Plugins register their event types and define the associated payload structures.

The runtime manages event infrastructure without requiring knowledge of specific event types.

Example event types may include collision events, input events, or application lifecycle events.

### 5.2 Asset Manager

The Asset Manager manages the lifecycle of assets.

Its responsibilities include:

- Asset loading
- Asset unloading
- Asset reloading
- Asset versioning
- Asset identification
- Asset type management

An asset consists of:

- Asset type
- Asset payload

Asset types are registered by plugins.

Plugins provide the functionality required to load, unload, and otherwise manage their asset types.

The Asset Manager provides the infrastructure required to manage assets independently of their specific types.

### 5.3 Resource Manager

The Resource Manager manages runtime resources.

A resource consists of:

- Resource type
- Resource payload

The Resource Manager maintains a resource pool and provides infrastructure for resource registration, storage, lookup, and lifecycle management.

Resource types are defined and registered by plugins.

Plugins provide the functionality required to create, destroy, and manage their resources.

Resources are intended to represent reusable runtime data or state that may be shared by multiple objects.

For example, a texture resource may be referenced by multiple sprite objects.

### 5.4 Object RTTI System

The Object RTTI System provides runtime type information and object management.

It consists of:

- Type registry
- Object pool
- Object type descriptors
- Object lifecycle management
- Object hierarchy infrastructure

Plugins register their object types with the runtime.

An object type descriptor provides the metadata and functionality required to manage instances of the corresponding type.

Type descriptors may contain:

- Type identification
- Type name
- Type metadata
- Properties
- Methods
- Construction functionality
- Destruction functionality
- Serialization functionality
- Update callbacks
- Type-specific flags

The runtime uses these descriptors to manage objects independently of their concrete implementations.

### 5.5 Object Pool

The Object Pool manages registered object instances.

The runtime owns all registered objects, regardless of which plugin created them.

Objects are created and destroyed through the runtime object management infrastructure.

The object pool is responsible for object storage and lifecycle management.

Plugins provide the functionality required to construct and destroy their object types.

An object may contain child objects, forming an object hierarchy.

The object pool and object hierarchy are distinct concepts. The object pool manages object instances, while the hierarchy defines relationships between objects.

### 5.6 Plugin Dependency Resolver

The Plugin Dependency Resolver manages plugin dependencies.

Dependencies are represented as a directed acyclic graph.

The resolver determines a valid initialization order and the corresponding reverse termination order.

The resolver must reject invalid dependency graphs, including circular dependencies.

---

## 6. Objects and Object Hierarchies

Objects are runtime instances of registered object types.

An object may contain properties, methods, and child objects.

Objects form hierarchical structures.

An object may have multiple children, and each child belongs to a parent in the object hierarchy.

The hierarchy is used to organize objects and define their relationships.

### 6.1 Object Creation

Objects are created through the runtime object management infrastructure.

An object must have a valid parent when it is inserted into the object hierarchy.

Object creation and hierarchy insertion may be deferred to prevent modifications to the hierarchy during traversal.

Newly created objects do not begin participating in the current update cycle if their insertion is deferred.

### 6.2 Object Destruction

Object destruction may be deferred until a safe point in the engine update cycle.

Objects scheduled for destruction are removed from the hierarchy and destroyed by the runtime.

The runtime is responsible for ensuring that object destruction does not invalidate active hierarchy traversal.

### 6.3 Object Properties

Objects may expose properties through their runtime type information.

Properties may be grouped into property groups.

Properties may be inspected or modified through runtime reflection and may be exposed to the scripting language.

### 6.4 Object Methods

Object types may expose methods through runtime type information.

Methods may be invoked through the runtime reflection system and may be exposed to the scripting language.

### 6.5 Object Update Callbacks

Objects may provide update callbacks.

The currently defined update phases are:

- Fixed Update
- Update
- Late Update

An object type may provide one or more of these callbacks.

Object types that do not provide update callbacks must be configured accordingly through their type metadata or flags.

The runtime must not attempt to invoke callbacks that are not provided by an object type.

---

## 7. Scene Architecture

A scene represents an object hierarchy used by an application.

A scene contains a root object and its associated object hierarchy.

Objects may contain child objects, allowing complex structures to be constructed from smaller objects.

For example, a player object may contain a sprite object, a collider object, and other component objects.

Scenes are provided by plugins and are not intrinsic object types known to the Runtime Layer.

Scene assets are managed through the Asset Manager.

The scene implementation is responsible for managing its object hierarchy and providing the functionality required to update its objects.

The runtime provides the object management infrastructure used by scenes.

---

## 8. Engine Lifecycle

The engine follows the following lifecycle:

1. Initialization
2. Runtime execution
3. Shutdown

### 8.1 Initialization

During initialization, the engine:

1. Initializes the required runtime subsystems.
2. Loads the engine configuration.
3. Resolves the dependencies of enabled plugins.
4. Initializes plugins in dependency order.
5. Initializes the functionality required by the application.

A plugin must not be initialized before its dependencies.

If initialization fails, the engine must terminate successfully initialized components in reverse initialization order and release associated resources.

### 8.2 Runtime Execution

The engine maintains its own execution loop.

During each iteration, the engine performs the operations required to advance the runtime.

The runtime subsystems are updated, followed by the execution of initialized plugins and the functionality provided by the application.

The engine update loop is responsible for coordinating the execution of runtime systems and plugin functionality.

The exact update sequence is defined by the engine update procedure.

### 8.3 Shutdown

During shutdown, the engine terminates initialized plugins in reverse dependency order.

After plugin termination, the engine terminates its runtime subsystems and releases associated resources.

The runtime must ensure that plugin-provided types, callbacks, and objects are no longer in use before plugin implementations are unloaded.

Shutdown must occur in a controlled order to prevent dependencies from being destroyed before their dependents.

---

## 9. Engine Update Procedure

The engine update procedure coordinates the execution of the runtime and application functionality.

The update procedure is responsible for:

- Processing events
- Updating assets
- Updating resources
- Managing objects
- Executing object update callbacks
- Updating initialized plugins
- Processing deferred operations

The object update procedure consists of the following phases:

1. Fixed Update
2. Update
3. Late Update

Each phase traverses the object hierarchy.

Children are updated before their parents.

An object only receives callbacks that are provided by its type.

The update procedure must ensure that hierarchy modifications do not invalidate active traversal.

### 9.1 Fixed Update

Fixed Update is executed for objects that provide a fixed update callback.

It is intended for functionality that requires a consistent time step.

### 9.2 Update

Update is executed for objects that provide an update callback.

It is intended for regular runtime functionality.

### 9.3 Late Update

Late Update is executed for objects that provide a late update callback.

It is intended for functionality that must execute after the regular update phase.

---

## 10. Ownership and Lifecycle

The runtime is responsible for managing the lifecycle of registered objects, resources, assets, and types.

Plugins provide the functionality required to manage their registered components.

The runtime maintains the infrastructure required to store and manage instances independently of their concrete implementations.

The ownership model is defined as follows:

- The Object Pool owns registered object instances.
- The Resource Manager owns registered resource instances.
- The Asset Manager owns managed asset instances.
- The Type Registry owns registered type metadata.
- The Plugin Manager manages plugin lifecycle.
- The object hierarchy defines object relationships, not independent ownership.

Object and resource references must remain valid according to the lifecycle rules of their respective managers.

Plugin termination must not leave registered types, callbacks, or instances referring to unloaded plugin implementations.

---

## 11. Configuration

The engine configuration determines which plugins are enabled and which configuration values are provided to the engine and its plugins.

Plugin configuration is used to determine the functionality available to the application.

The engine configuration must be processed before plugin initialization.

Plugin dependencies must be resolved against the enabled plugins.

A plugin whose required dependency is disabled must not be initialized.

---

## 12. Scripting

The engine is intended to support an integrated scripting language.

The scripting system will be provided through a plugin.

The scripting language may interact with the runtime through:

- Runtime type information
- Object properties
- Object methods
- Plugin-provided functions
- Runtime metadata
- Object flags and attributes

The scripting system is not part of the initial Runtime Layer implementation.

The runtime architecture is intended to provide the infrastructure necessary for scripting integration.

---

## 13. Editor

Angry Rocket is intended to provide an editor.

The editor is not required for the initial engine implementation.

The editor will interact with the engine through the interfaces provided by the engine and its plugins.

The editor may provide functionality for managing scenes, objects, properties, assets, resources, and application configuration.

---

## 14. Architectural Principles

The engine follows these principles:

- Separation of concerns
- Platform independence
- Modular architecture
- Explicit ownership
- Plugin-based extensibility
- Runtime type information
- Reusable infrastructure
- Dependency-driven initialization
- Reverse dependency termination
- Separation of assets, resources, and objects
- Separation of object storage and object hierarchy
- Application independence from engine-specific functionality
- Engine functionality provided through contracts

These principles guide the design and implementation of Angry Rocket.

---

## 15. Open Architectural Questions

The following architectural questions remain subject to further design decisions:

- Plugin unloading during runtime
- Plugin failure handling during runtime
- Object ownership and plugin association
- Object hierarchy mutation during updates
- Deferred object creation and destruction
- Scene lifecycle
- Resource reference management
- Asset reference management
- Runtime type registration and removal
- Plugin-provided callback lifetime
- Engine update ordering
- Threading model
- Serialization architecture
- Scripting integration
- Editor integration
