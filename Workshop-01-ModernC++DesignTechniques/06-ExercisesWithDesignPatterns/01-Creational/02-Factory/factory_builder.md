/**
 * The Builder, Factory Method, and Abstract Factory patterns are all creational design patterns that deal with object creation mechanisms. They are intended to provide a way to decouple clients from the classes of the objects that need to be created.
 * 
 * Builder Pattern:
 * The Builder pattern is used to construct a complex object step by step and the final step will return the object. It is suitable when there is a need to build different immutable objects that have the same construction process but different representations. The Builder pattern can be used to enforce a sequence of steps to create an object.
 * This pattern helps to solve the problem of having a constructor with too many parameters, or when the object creation process needs to be made more explicit, or when some steps of creation process are optional.
 *
 * Factory Method Pattern:
 * The Factory Method pattern provides a way to delegate the instantiation logic to child classes. It is used when a class can't anticipate the type of the objects it needs to create and wants its subclasses to specify the objects it creates. The Factory Method pattern can be used when there is a need to decouple the product implementation from the use of the product.
 * This pattern solves the problem of creating product objects without specifying their concrete classes.
 *
 * Abstract Factory Pattern:
 * The Abstract Factory pattern provides a way to encapsulate a group of individual factories that have a common theme without specifying their concrete classes. It is useful when the system needs to be independent from the way the products it works with are created.
 * This pattern solves the problem of creating families of related or dependent objects without specifying their concrete classes.
 * 
 * In terms of design principles, all these patterns adhere to the principle of 'programming to an interface, not an implementation' by decoupling the client code from the specific classes of the objects that are created. They also follow the 'Open/Closed Principle' by allowing new types of objects to be created without changing the client code.
 *
 * However, there are differences in their use cases and how they solve design problems. The Builder pattern is more about constructing complex objects step by step, possibly using different build steps or different representations. The Factory Method is about allowing subclasses to choose the concrete class of the object that will be created, while the Abstract Factory is about creating families of related objects.
 */