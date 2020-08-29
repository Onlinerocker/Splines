
# Readme

## Question 2: Degree-2 Bezier Curves

In class, we derived the Bezier curve for cubic interpolation. For this
question, derive the Bezier curve for a degree-2 polynomial.

### 2a. (5 points) In class, we saw that the formula for a nth-degree Bezier curve is

\\(
p(t) = \sum_{i=0}^n B_i^n(t) b_i
\\)

What is the polynomial for a degree-2 Bezier curve? How many control points does it have?

=(1-t)^2 + 2*t*(1-t) + t^2

### 2b. (5 points) How can we use de Casteljau's algorithm to interpolate using a degree-2 Bezier curve?

First, we would use linear interpolation to interpolate between b0 and b1 => LERP(b0, b1, t) = b0'
and b1 and b2 => LERP(b1, b2, t) = b1'

We would then use linear interpolation to interpolate between these two resuls => LERP(b0', b1', t) = ANSWER

## How many hours did you work on this assignment (outside of lab)

2

## What was the hardest part of this assignment?

Deriving the degree-2 bezier curve

## What was the easiest part of this assignment?

Implementation of linear interpolation

## Did you complete any extra credits?  If so, how do I run them and where is the video?

<style TYPE="text/css">
code.has-jax {font: inherit; font-size: 100%; background: inherit; border: inherit;}
</style>
<script type="text/x-mathjax-config">
MathJax.Hub.Config({
    tex2jax: {
        inlineMath: [['$','$'], ['\\(','\\)']],
        skipTags: ['script', 'noscript', 'style', 'textarea', 'pre'] // removed 'code' entry
    }
});
MathJax.Hub.Queue(function() {
    var all = MathJax.Hub.getAllJax(), i;
    for(i = 0; i < all.length; i += 1) {
        all[i].SourceElement().parentNode.className += ' has-jax';
    }
});
</script>
<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.4/MathJax.js?config=TeX-AMS_HTML-full"></script>
