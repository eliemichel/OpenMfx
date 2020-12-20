#include <PluginSupport/MfxRegister>

#include <PluginSupport/MfxEffect>

class TranslateEffect : public MfxEffect {
	protected:
	OfxStatus Describe(OfxMeshEffectHandle descriptor) override {
		AddInput(kOfxMeshMainInput);
		AddInput(kOfxMeshMainOutput);
		// Add a vector3 parameter
		AddParam("translation", double3{0.0, 0.0, 0.0})
		.Label("Translation") // Name used for display
		.Range(double3{-10.0, -10.0, -10.0}, double3{10.0, 10.0, 10.0});
		
		// Add a bool parameter
		AddParam("tickme", false)
		.Label("Tick me!");
		return kOfxStatOK;

	}
	
	OfxStatus Cook(OfxMeshEffectHandle instance) override {
		MfxMesh input_mesh = GetInput(kOfxMeshMainInput).GetMesh();
		MfxAttributeProps input_positions;
		input_mesh.GetPointAttribute(kOfxMeshAttribPointPosition)
			.FetchProperties(input_positions);

		double3 translation = GetParam<double3>("translation").GetValue();

		MfxMeshProps input_mesh_props;
		input_mesh.FetchProperties(input_mesh_props);
		int output_point_count = input_mesh_props.pointCount;
		int output_vertex_count = input_mesh_props.vertexCount;
		int output_face_count = input_mesh_props.faceCount;
		
		// Extra properties related to memory usage optimization
		int output_no_loose_edge = input_mesh_props.noLooseEdge;
		int output_constant_face_count = input_mesh_props.constantFaceCount;

		MfxMesh output_mesh = GetInput(kOfxMeshMainOutput).GetMesh();
		
		output_mesh.GetVertexAttribute(kOfxMeshAttribVertexPoint)
			.ForwardFrom(input_mesh.GetVertexAttribute(kOfxMeshAttribVertexPoint));
		
		output_mesh.GetFaceAttribute(kOfxMeshAttribFaceCounts)
			.ForwardFrom(input_mesh.GetFaceAttribute(kOfxMeshAttribFaceCounts));

		
		output_mesh.Allocate(
			output_point_count,
			output_vertex_count,
			output_face_count,
			output_no_loose_edge,
			output_constant_face_count);

		MfxAttributeProps output_positions;
		output_mesh.GetPointAttribute(kOfxMeshAttribPointPosition)
			.FetchProperties(output_positions);
		
		// (NB: This can totally benefit from parallelization using e.g. OpenMP)
		for (int i = 0 ; i < output_point_count ; ++i) {
			float *in_p = reinterpret_cast<float*>(input_positions.data + i * input_positions.stride);
			float *out_p = reinterpret_cast<float*>(output_positions.data + i * output_positions.stride);
			out_p[0] = in_p[0] + translation[0];
			out_p[1] = in_p[1] + translation[1];
			out_p[2] = in_p[2] + translation[2];
		}

		output_mesh.Release();
		input_mesh.Release();

		return kOfxStatOK;

	}
	public:
	const char* GetName() override {
		return "Translate";
	}

};

class ArrayEffect : public MfxEffect {
public:
	const char* GetName() override {
		return "Array";
	}
protected:
	OfxStatus Describe(OfxMeshEffectHandle descriptor) override {
		AddInput(kOfxMeshMainInput)
		.RequestVertexAttribute(
			"uv0",
			2, kOfxMeshAttribTypeFloat,
			kOfxMeshAttribSemanticTextureCoordinate,
			false /* not mandatory */
		);
		
		AddInput(kOfxMeshMainOutput);

		// Number of copies
		AddParam("count", 2)
		.Label("Count")
		.Range(0, 2147483647);
		
		// Translation added at each copy
		AddParam("translation", double3{0.0, 0.0, 0.0})
		.Label("Translation")
		.Range(double3{-10.0, -10.0, -10.0}, double3{10.0, 10.0, 10.0});
		AddParam("offset_uv", false)
		.Label("Offset UVs");

		return kOfxStatOK;
	}

	OfxStatus Cook(OfxMeshEffectHandle instance) override {
		MfxMesh input_mesh = GetInput(kOfxMeshMainInput).GetMesh();
		MfxMeshProps input_props;
		input_mesh.FetchProperties(input_props);
		
		int count = GetParam<int>("count").GetValue();
		double3 translation = GetParam<double3>("translation").GetValue();
		bool offset_uv = GetParam<bool>("offset_uv").GetValue();
		MfxAttributeProps input_uv;
		if (offset_uv && input_mesh.HasVertexAttribute("uv0")) {
			input_mesh.GetVertexAttribute("uv0").FetchProperties(input_uv);
			if (input_uv.componentCount < 2 || input_uv.type != MfxAttributeType::Float) {
				offset_uv = false; // incompatible type, so we deactivate this feature
			}
		} else {
			offset_uv = false; // no uv available, so here again we deactivate this feature
		}

		MfxMesh output_mesh = GetInput(kOfxMeshMainOutput).GetMesh();
		
		if (offset_uv) {
			output_mesh.AddVertexAttribute(
				"uv0",
				2, kOfxMeshAttribTypeFloat,
				kOfxMeshAttribSemanticTextureCoordinate
			);
		}

		
		output_mesh.Allocate(
			input_props.pointCount * count,
			input_props.vertexCount * count,
			input_props.faceCount * count,
			input_props.noLooseEdge,
			input_props.constantFaceCount);

		MfxAttributeProps input_positions, input_vert_points, input_face_counts;
		input_mesh.GetPointAttribute(kOfxMeshAttribPointPosition).FetchProperties(input_positions);
		input_mesh.GetVertexAttribute(kOfxMeshAttribVertexPoint).FetchProperties(input_vert_points);
		input_mesh.GetFaceAttribute(kOfxMeshAttribFaceCounts).FetchProperties(input_face_counts);
		
		MfxAttributeProps output_positions, output_vert_points, output_face_counts;
		output_mesh.GetPointAttribute(kOfxMeshAttribPointPosition).FetchProperties(output_positions);
		output_mesh.GetVertexAttribute(kOfxMeshAttribVertexPoint).FetchProperties(output_vert_points);
		output_mesh.GetFaceAttribute(kOfxMeshAttribFaceCounts).FetchProperties(output_face_counts);
		for (int k = 0 ; k < count ; ++k) {
			for (int i = 0 ; i < input_props.pointCount ; ++i) {
				int j = i + k * input_props.pointCount;
				float *in_p = reinterpret_cast<float*>(input_positions.data + i * input_positions.stride);
				float *out_p = reinterpret_cast<float*>(output_positions.data + j * output_positions.stride);
				out_p[0] = in_p[0] + translation[0] * k;
				out_p[1] = in_p[1] + translation[1] * k;
				out_p[2] = in_p[2] + translation[2] * k;
			}

			for (int i = 0 ; i < input_props.vertexCount ; ++i) {
				int j = i + k * input_props.vertexCount;
				int *in_p = reinterpret_cast<int*>(input_vert_points.data + i * input_vert_points.stride);
				int *out_p = reinterpret_cast<int*>(output_vert_points.data + j * output_vert_points.stride);
				out_p[0] = in_p[0] + k * input_props.pointCount;
			}

			if (input_props.constantFaceCount < 0) {
				for (int i = 0 ; i < input_props.faceCount ; ++i) {
					int j = i + k * input_props.faceCount;
					int *in_p = reinterpret_cast<int*>(input_face_counts.data + i * input_face_counts.stride);
					int *out_p = reinterpret_cast<int*>(output_face_counts.data + j * output_face_counts.stride);
					out_p[0] = in_p[0];
				}

			}
		}
		if (offset_uv) {
			MfxAttributeProps output_uv;
			output_mesh.GetVertexAttribute("uv0").FetchProperties(output_uv);
		
			for (int k = 0 ; k < count ; ++k) {
				for (int i = 0 ; i < input_props.vertexCount ; ++i) {
					int j = i + k * input_props.vertexCount;
					float *in_p = reinterpret_cast<float*>(input_uv.data + i * input_uv.stride);
					float *out_p = reinterpret_cast<float*>(output_uv.data + j * output_uv.stride);
					out_p[0] = in_p[0] + k;
					out_p[1] = in_p[1];
				}

			}
		}

		
		output_mesh.Release();
		input_mesh.Release();
		return kOfxStatOK;

	}
};


MfxRegister(
    TranslateEffect,
    ArrayEffect
);

