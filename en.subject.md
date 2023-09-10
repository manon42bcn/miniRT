# My ﬁrst RayTracer with miniLibX #

*Summary:* *This* *project* *is* *an* *introduction* *to* *the*
*beautiful* *world* *of* *Raytracing.* *Once* *completed* *you* *will*
*be* *able* *to* *render* *simple* *Computer-Generated-Images* *and*
*you*

*Version:* *7*

**Contents**

**I** **Introduction** **2**

**II** **Common** **Instructions** **3**

**III** **Mandatory** **part** **-** **miniRT** **4**

**IV** **Bonus** **part** **9**

**V** **Examples** **11**

**Chapter** **I**

**Introduction**

When it comes to rendering 3-dimensional computer-generated images there
are 2 possi-ble approaches: "Rasterization", which is used by almost all
graphic engines because of its eﬃciency and "Ray Tracing."

The "Ray Tracing" method, developed for the ﬁrst time in 1968 (but
improved upon since) is even today more expensive in computation than
the "Rasterization" method. As a result, it is not yet fully adapted to
real time use-cases but it produce a much higher degree of visual
realism.

> Figure I.1: The pictures above are rendered with the ray tracing
> technique. Impressive isn't it?

Before you can even begin to produce such high-quality graphics, you
must mas-ter the basics: the miniRT is your ﬁrst ray tracer coded in C,
normed and humble but functionnal.

The main goal of miniRT is to prove to yourself that you can implement
any mathe-matics or physics formulas without being a mathematician, we
will only implement the most basics ray tracing features here so just
keep calm, take a deep breath and don't panic! After this project you'll
be able to show oﬀ nice-looking pictures to justify the number of hours
you're spending at school\...


**Common** **Instructions**

> • Your project must be written in C.
>
> • Your project must be written in accordance with the Norm. If you
> have bonus ﬁles/functions, they are included in the norm check and you
> will receive a 0 if there is a norm error inside.
>
> • Your functions should not quit unexpectedly (segmentation fault, bus
> error, double free, etc) apart from undeﬁned behaviors. If this
> happens, your project will be considered non functional and will
> receive a 0 during the evaluation.
>
> • All heap allocated memory space must be properly freed when
> necessary. No leaks will be tolerated.
>
> • If the subject requires it, you must submit a Makefile which will
> compile your source ﬁles to the required output with the ﬂags -Wall,
> -Wextra and -Werror, use cc, and your Makeﬁle must not relink.
>
> • Your Makefile must at least contain the rules \$(NAME), all, clean,
> fclean and re.
>
> • To turn in bonuses to your project, you must include a rule bonus to
> your Makeﬁle, which will add all the various headers, librairies or
> functions that are forbidden on the main part of the project. Bonuses
> must be in a diﬀerent ﬁle \_bonus.{c/h}. Mandatory and bonus part
> evaluation is done separately.
>
> • If your project allows you to use your libft, you must copy its
> sources and its associated Makefile in a libft folder with its
> associated Makeﬁle. Your project's Makefile must compile the library
> by using its Makefile, then compile the project.
>
> • We encourage you to create test programs for your project even
> though this work **won't** **have** **to** **be** **submitted**
> **and** **won't** **be** **graded**. It will give you a chance to
> easily test your work and your peers' work. You will ﬁnd those tests
> especially useful during your defence. Indeed, during defence, you are
> free to use your tests and/or the tests of the peer you are
> evaluating.
>
> • Submit your work to your assigned git repository. Only the work in
> the git reposi-tory will be graded. If Deepthought is assigned to
> grade your work, it will be done after your peer-evaluations. If an
> error happens in any section of your work during Deepthought's
> grading, the evaluation will stop.

**Mandatory** **part** **-** **miniRT**

> The constraints are as follows:
>
> • You must use the miniLibX. Either the version that is available on
> the operating system, or from its sources. If you choose to work with
> the sources, you will need to apply the same rules for your libft as
> those written above in Common Instructions part.
>
> • The management of your window must remain smooth: changing to
> another win-dow, minimizing, etc.
>
> • You need at least these 3 simple geometric objects: plane, sphere,
> cylinder.
>
> • If applicable, all possible intersections and the inside of the
> object must be handled correctly.

> • Your program must be able to resize the object's unique properties:
> diameter for a sphere and the width and height for a cylinder.
>
> • Your program must be able to apply translation and rotation
> transformation to objects, lights and cameras (except for spheres and
> lights that cannot be rotated).
>
> • Light management: spot brightness, hard shadows, ambiance lighting
> (objects are never completely in the dark). You must implement Ambient
> and diﬀuse lighting.
>
> • the program displays the image in a window and respect the following
> rules:
>
> ◦ Pressing ESC must close the window and quit the program cleanly.
>
> ◦ Clicking on the red cross on the window's frame must close the
> window and quit the program cleanly.
>
> ◦ The use of images of the minilibX is strongly recommended.
>
> • Your program must take as a ﬁrst argument a scene description ﬁle
> with the .rt extension.
>
> ◦ Each type of element can be separated by one or more line break(s).
>
> ◦ Each type of information from an element can be separated by one or
> more space(s).
>
> ◦ Each type of element can be set in any order in the ﬁle.
>
> ◦ Elements which are deﬁned by a capital letter can only be declared
> once in the scene.
>
> ◦ Each element ﬁrst's information is the type identiﬁer (composed by
> one or two character(s)), followed by all speciﬁc information for each
> object in a strict order such as:
>
> ◦ **Ambient** **lightning:**
>
> A 0.2 255,255,255
>
> ∗ identiﬁer: **A**
>
> ∗ ambient lighting ratio in range \[0.0,1.0\]: **0.2** ∗ R,G,B colors
> in range \[0-255\]: **255,** **255,** **255**
>
> ◦ **Camera:**
>
> C -50.0,0,20 0,0,1 70
>
> ∗ identiﬁer: **C**
>
> ∗ x,y,z coordinates of the view point: **0.0,0.0,20.6**
>
> ∗ 3d normalized orientation vector. In range \[-1,1\] for each x,y,z
> axis: **0.0,0.0,1.0**
>
> ∗ FOV : Horizontal ﬁeld of view in degrees in range \[0,180\]
>
> ◦ **Light:**
>
> L -40.0,50.0,0.0 0.6 10,0,255
>
> ∗ identiﬁer: **L**
>
> ∗ x,y,z coordinates of the light point: **0.0,0.0,20.6** ∗ the light
> brightness ratio in range \[0.0,1.0\]: **0.6**
>
> ∗ (unused in mandatory part)R,G,B colors in range \[0-255\]: **10,**
> **0,** **255**
>
> ◦ **Sphere**:
>
> sp 0.0,0.0,20.6 12.6 10,0,255
>
> ∗ identiﬁer: **sp**
>
> ∗ x,y,z coordinates of the sphere center: **0.0,0.0,20.6** ∗ the
> sphere diameter: **12.6**
>
> ∗ R,G,B colors in range \[0-255\]: **10,** **0,** **255**
>
> ◦ **Plane:**
>
> pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
>
> ∗ identiﬁer: **pl**
>
> ∗ x,y,z coordinates: **0.0,0.0,-10.0**
>
> ∗ 3d normalized orientation vector. In range \[-1,1\] for each x,y,z
> axis: **0.0,0.0,1.0**
>
> ∗ R,G,B colors in range \[0-255\]: **0,** **0,** **255**
>
> ◦ **Cylinder:**
>
> cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
>
> ∗ identiﬁer: **cy**
>
> ∗ x,y,z coordinates: **50.0,0.0,20.6**
>
> ∗ 3d normalized orientation vector. In range \[-1,1\] for each x,y,z
> axis: **0.0,0.0,1.0**
>
> ∗ the cylinder diameter: **14.2** ∗ the cylinder height: **21.42**
>
> ∗ R,G,B colors in range \[0,255\]: **10,** **0,** **255**
>

> • Example of the mandatory part with a minimalist **.rt** scene:
>
> A 0.2
>
> C -50,0,20 0,0,0 70 L -40,0,30 0.7

255,255,255

255,255,255

> pl 0,0,0 0,1.0,0 sp 0,0,20
>
> cy 50.0,0.0,20.6 0,0,1.0 20 14.2 21.42

255,0,225 255,0,0 10,0,255

> • If any misconﬁguration of any kind is encountered in the ﬁle the
> program must exit properly and return \"Error\\n\" followed by an
> explicit error message of your choice.
>
> • For the defense, it would be ideal for you to have a whole set of
> scenes with the focus on what is functional, to facilitate the control
> of the elements to create.

**Bonus** **part**

The Ray-Tracing technique could handle many more things like reﬂection,
transparency, refraction, more complex objects, soft shadows, caustics,
global illumination, bump map-ping, .obj ﬁle rendering etc..

But for the miniRT project, we want to keep things simple for your ﬁrst
raytracer and your ﬁrst steps in CGI.

So here is a list of few simple bonuses you could implement, if you want
to do bigger bonuses we strongly advise you to recode a new ray-tracer
later in your developer life after this little one is ﬁnished and fully
functionnal.

Figure IV.1: A spot, a space skybox and a shiny earth-textured sphere
with bump-maping

> Bonuses will be evaluated only if your mandatory part is PERFECT. By
> PERFECT we naturally mean that it needs to be complete, that it cannot
> fail, even in cases of nasty mistakes like wrong uses etc. It means
> that if your mandatory part does not obtain ALL the points during the
> grading, your bonuses will be entirely IGNORED.

> Bonus list:
>
> • Add specular reﬂection to have a full Phong reﬂection model.
>
> • Color disruption: checkerboard.
>
> • Colored and multi-spot lights.
>
> • One other 2nd degree object: Cone, Hyperboloid, Paraboloid..
>
> • Handle bump map textures.
>
> You are allowed to use other functions and add features to your scene
> description to complete the bonus part as long as their use is
>
> justified during your evaluation. You are also allowed to modify the
> expected scene file format to fit your needs. Be smart!
>