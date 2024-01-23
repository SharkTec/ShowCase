Greetings, reader!

This project is a small showcase of my coding style

What functionality is offered:

1. Browse and find an image on your computer
2. Load an image (not all image formats are supported) -> image loading is not done automatically after browsing because there can
be some pretty demanding image formats and resolutions. So in order to prevent people misclicking and waiting ~10s for loading an image
they don't want, I made this with an additional button
3. OPTIONAL (fit image to current window size)
4. Filter image (filter kernel/convolution matrix consists of some default parameters I found online; should provide some edge detection, quality of
result depends on the image. It's just an exemplary implementation, not a full-fledged canny edge detector). The logic behind the filterImage function
was written several years ago for academic purposes. For this showcase application, I merely included it.

Remark for anyone who doesn't have Qt installed:

In the img folder there are two images of how the application looks and what it does

Disclaimer: The image is not mine. I do not own it.

