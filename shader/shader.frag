uniform float percent;
uniform sampler2D texture;
uniform vec4 flashColor;

void main()
{
    vec4 pixel_color = texture2D(texture, gl_TexCoord[0].xy);

    vec4 colorDifference = vec4(0,0,0,1);

    if (pixel_color != vec4(0, 0, 0, 1))
    {
        pixel_color = mix(pixel_color, flashColor, percent);
    }

    gl_FragColor = pixel_color; 
}