Slug
=====
Slug, named after the terrestrial gastropod mollusc that travels on a lubricating film, is a Hyperloop air bearing analysis tool built on the MOOSE multiphysics framework.

For more on the MOOSE Framework see: [http://mooseframework.org/](http://mooseframework.org/)

Installation
-------------
First set up the Moose Framework following the instructions here:
[http://mooseframework.org/getting-started/](http://mooseframework.org/getting-started/)

Clone the slug repository:

    git clone https://github.com/adamLange/slug.git

Go to the slug directory and compile the source:

    make -j <number of parallel processes>

Execute the test script in the slug directory:

    ./run_tests

If that works, you should be good to go!  Now start revolutionizing transportation!

Documentation
-------------
See slug/doc

> Written with [StackEdit](https://stackedit.io/).

Example Problems
----------------
See the external examples repository [https://github.com/adamLange/slug-examples](https://github.com/adamLange/slug-examples)
