#version 420 core

// https://mathstat.slu.edu/escher/index.php/Spherical_Geometry
// https://stackoverflow.com/questions/5963954/fast-templated-c-octree-implementation#8423694
// https://gamedev.stackexchange.com/questions/184631/using-octrees-as-lod-system

// how many times this shader will run per patch (nº of out control points)
layout(vertices = 4) out;

uniform vec3 impact;

in block
{
    vec3 position;
} In[];

out block
{
    vec3 position;
} Out[];

struct AABB {
  float radius;
  vec3 center;
};

struct Octree {
  AABB bound;
  int lod;
};

const int maxLOD = 3;

buffer OctreeBuffer { Octree u_OctreeBuffer[]; };
uniform atomic_uint u_OctreeBufferCount;

// https://math.stackexchange.com/questions/1472049/check-if-a-point-is-inside-a-rectangular-shaped-area-3d
bool Contains(AABB bound, vec3 point) {
  vec3 p1 = vec3(bound.center.x + bound.radius, bound.center.y + bound.radius, bound.center.z + bound.radius);
  vec3 p2 = vec3(bound.center.x - bound.radius, bound.center.y + bound.radius, bound.center.z + bound.radius);
  vec3 p3 = vec3(bound.center.x + bound.radius, bound.center.y - bound.radius, bound.center.z + bound.radius);
  vec3 p4 = vec3(bound.center.x + bound.radius, bound.center.y + bound.radius, bound.center.z - bound.radius);
  vec3 p5 = vec3(bound.center.x - bound.radius, bound.center.y - bound.radius, bound.center.z + bound.radius);
  vec3 p6 = vec3(bound.center.x + bound.radius, bound.center.y - bound.radius, bound.center.z - bound.radius);
  vec3 p7 = vec3(bound.center.x - bound.radius, bound.center.y + bound.radius, bound.center.z - bound.radius);
  vec3 p8 = vec3(bound.center.x - bound.radius, bound.center.y - bound.radius, bound.center.z - bound.radius);

  vec3 u = p2 - p1;
  vec3 v = p2 - p7;
  vec3 w = p2 - p5;

  float du = dot(u, point);
  float dv = dot(v, point);
  float dw = dot(w, point);

  return (
	  (dot(u, p2) <= du && du <= dot(u, p1)) &&
	  (dot(u, p2) <= dv && dv <= dot(u, p7)) &&
	  (dot(u, p2) <= dw && dw <= dot(u, p5))
	);
}

AABB ComputeAABB(AABB bound) {
  vec3 boundOffsetTable[8] = {{-0.5, -0.5, -0.5}, {+0.5, -0.5, -0.5}, {-0.5, +0.5, -0.5}, {+0.5, +0.5, -0.5},
                                {-0.5, -0.5, +0.5}, {+0.5, -0.5, +0.5}, {-0.5, +0.5, +0.5}, {+0.5, +0.5, +0.5}};

  vec3 offset = boundOffsetTable[i] * bound.radius;

  return AABB(bound.radius * 0.5, bound.center + offset);
}

void BuildOctreeRoot(vec3 impact) {
	uint idx            = atomicCounterIncrement(u_OctreeBufferCount);
	u_OctreeBuffer[idx] = Octree(AABB(), 1);
	BuildOctree(u_OctreeBuffer[idx], impact);
}

void BuildOctreeChild(Octree self, vec3 impact) {
	if (Contains(self.bound, impact) && self.lod < maxLOD) {
		uint idx            = atomicCounterIncrement(u_OctreeBufferCount);
		u_OctreeBuffer[idx] = Octree(ComputeAABB(self.bound), self.lod + 1);
		BuildOctree(u_OctreeBuffer[idx], impact);
	}
}

void main() {
  BuildOctreeRoot(impact)
}