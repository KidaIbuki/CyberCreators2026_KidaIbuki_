xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 34;
 1.86379;1.08940;4.96175;,
 2.81102;0.36256;4.96175;,
 2.81102;0.36256;-7.94284;,
 1.86379;1.08940;-7.94284;,
 2.96688;-0.82120;4.96175;,
 2.96688;-0.82120;-7.94284;,
 2.24003;-1.76844;4.96175;,
 2.24003;-1.76844;-7.94284;,
 1.05627;-1.92428;4.96175;,
 1.05627;-1.92428;-7.94284;,
 0.10903;-1.19744;4.96175;,
 0.10903;-1.19744;-7.94284;,
 -0.04682;-0.01368;4.96175;,
 -0.04682;-0.01368;-7.94284;,
 0.68003;0.93356;4.96175;,
 0.68003;0.93356;-7.94284;,
 1.86379;1.08940;4.96175;,
 1.86379;1.08940;-7.94284;,
 1.46002;-0.41744;4.10806;,
 1.46002;-0.41744;4.10806;,
 1.46002;-0.41744;4.10806;,
 1.46002;-0.41744;4.10806;,
 1.46002;-0.41744;4.10806;,
 1.46002;-0.41744;4.10806;,
 1.46002;-0.41744;4.10806;,
 1.46002;-0.41744;4.10806;,
 1.46002;-0.41744;-10.66201;,
 1.46002;-0.41744;-10.66201;,
 1.46002;-0.41744;-10.66201;,
 1.46002;-0.41744;-10.66201;,
 1.46002;-0.41744;-10.66201;,
 1.46002;-0.41744;-10.66201;,
 1.46002;-0.41744;-10.66201;,
 1.46002;-0.41744;-10.66201;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;;
 
 MeshMaterialList {
  15;
  24;
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8;;
  Material {
   0.624000;0.624000;0.624000;1.000000;;
   5.000000;
   0.216000;0.216000;0.216000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.298400;0.019200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.514400;0.800000;0.329600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.800000;0.401600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.661600;0.661600;0.661600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.279200;0.191200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.790400;0.589600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.436000;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.269600;0.269600;0.269600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;0.660000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.179200;0.800000;0.132000;0.860000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.100000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.540000;0.768800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  0.000001;-0.000001;1.000000;,
  0.258823;0.965925;0.000000;,
  0.866023;0.500004;0.000000;,
  0.965927;-0.258815;-0.000000;,
  0.499996;-0.866028;-0.000000;,
  -0.258820;-0.965926;0.000000;,
  -0.866024;-0.500003;0.000000;,
  -0.965926;0.258819;0.000000;,
  -0.499996;0.866028;0.000000;,
  0.249930;0.932738;-0.259873;,
  0.836269;0.482825;-0.259873;,
  0.932740;-0.249923;-0.259875;,
  0.482817;-0.836273;-0.259874;,
  -0.249928;-0.932739;-0.259872;,
  -0.836270;-0.482824;-0.259872;,
  -0.932739;0.249927;-0.259873;,
  -0.482818;0.836273;-0.259872;,
  0.827984;0.109009;-0.550054;,
  -0.415740;-0.240031;0.877237;,
  -0.124249;-0.463699;0.877237;,
  -0.463696;0.124245;0.877239;,
  -0.240025;0.415742;0.877238;,
  0.124249;0.463701;0.877237;,
  0.415742;0.240031;0.877236;,
  0.463700;-0.124248;0.877237;,
  0.240027;-0.415743;0.877237;,
  -0.508396;-0.662555;-0.550049;,
  -0.433693;0.751186;-0.497625;;
  24;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  3;0,18,19;,
  3;0,20,18;,
  3;0,21,20;,
  3;0,22,21;,
  3;0,23,22;,
  3;0,24,23;,
  3;0,25,24;,
  3;0,19,25;,
  3;17,9,10;,
  3;17,10,11;,
  3;17,11,12;,
  3;26,12,13;,
  3;26,13,14;,
  3;26,14,15;,
  3;27,15,16;,
  3;27,16,9;;
 }
 MeshTextureCoords {
  34;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
