void main()
{
    // Transform the vertex m_position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
