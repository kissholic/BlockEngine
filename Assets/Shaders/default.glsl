@ctype mat4 glm::mat4
@ctype vec4 glm::vec4
@ctype vec3 glm::vec3

@vs vs
uniform vs_params {
    mat4 mvp;
};

@layout_type vec4
layout(location=0) in vec4 position;
layout(location=1) in vec4 color0;

out vec4 color;

void main() {
    gl_Position = mvp * position;
    color = color0;
}
@end

@fs fs
in vec4 color;

out vec4 frag_color;

void main() {
    frag_color = color;
}
@end

@program default vs fs
