# Vein-based-authentication-system

An authentication system based on the veins in the palm dorsal of hands.

![Homepage](https://raw.githubusercontent.com/mimikian/Vein-based-authentication-system/master/imgs/cover.png)

## Keywords
- Thermal Imaging
- Interactive Surfaces
- User Authentication
- User Identification
- Collaboration

## What is it?
A veinbased authentication mechanism by combining thermal imaging
and computer vision. 

The system consisted of four main stages which are:

- Image Acquisition: Is done by utilizing Optris PI 450 thermal camera to capture the veins. 

- Image Enhancement: By using several noise reduction filters like Gaussian filter and mean filter. 

- Image Segmentation: Extracting the skeleton of the veins using Morphological Transformations like Dilation and Erosion. 

- Image Matching: We used two algorithms which are Hausdorff distance and 
Shape context to calculate the error of similarity between two images. 

To evaluate our system we conducted a study to authenticate users.
The system was trained using dataset consisting of 42 images collected from 14 persons with age average 22.5 and SD 3.56802. For each user the Hausdorff distance and shape context calculated by taking the mean of two samples from the corresponding user in the dataset.

The results were measured by two main metrics which are False Acceptance Rate and True
Acceptance Rate. Hausdorff distance achieved FAR 0% and TAR 100% with threshold value
9 and Shape context achieved FAR 21% and TAR 29% with threshold value 2. The failure to enroll when constructing the dataset was 50%. 

Further we proposed a prototype allowing novel customized multi-user interaction on arbitrary surface, through identifying the users during the interaction session based on their heat signature irrespective to the angle of approach and without the need for instrumenting the surface nor the users enabling the users to interactive
freely anywhere.

The first five steps of the vein extraction algorithm. After
capturing an image from the camera, it is filtered and converted to
grayscale, an adaptive threshold is applied, the region of interest is extracted
and finally the veins are extracted.

![Homepage](https://raw.githubusercontent.com/mimikian/Vein-based-authentication-system/master/imgs/stages.png)

##Note
The project is still under research. For more information you can check:
[VID Paper](paper/VID.pdf)

