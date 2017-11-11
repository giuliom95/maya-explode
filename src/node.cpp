#include <string.h>
#include <maya/MIOStream.h>
#include <math.h>

#include <maya/MPxNode.h> 

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnPlugin.h>

#include <maya/MString.h> 
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>
#include <maya/MVector.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
 
class explodeGroup : public MPxNode {
public:
						explodeGroup();
	virtual				~explodeGroup(); 

	virtual MStatus		compute( const MPlug& plug, MDataBlock& data );

	static  void*		creator();
	static  MStatus		initialize();

public:
	static  MObject		input;		// The input value.
	static  MObject		output;		// The output value.
	static	MTypeId		id;
};

MTypeId	explodeGroup::id( 0x000ff );
MObject	explodeGroup::input;
MObject	explodeGroup::output;

explodeGroup::explodeGroup() {}
explodeGroup::~explodeGroup() {}

MStatus explodeGroup::compute( const MPlug& plug, MDataBlock& data ) {
	
	MStatus returnStatus;
 
	/*if( plug == output )
	{
		MDataHandle inputData = data.inputValue( input, &returnStatus );

		if( returnStatus != MS::kSuccess )
			cerr << "ERROR getting data" << endl;
		else
		{
			float result = sinf( inputData.asFloat() ) * 10.0f;
			MDataHandle outputHandle = data.outputValue( explodeGroup::output );
			outputHandle.set( result );
			data.setClean(plug);
		}
	} else {
		return MS::kUnknownParameter;
	}*/

	return MS::kSuccess;
}

void* explodeGroup::creator()
{
	return new explodeGroup();
}

MStatus explodeGroup::initialize()
{
	MFnNumericAttribute nAttr;
	MStatus				stat;

	input = nAttr.create( "input", "in", MFnNumericData::kFloat, 0.0 );
 	nAttr.setStorable(true);

	output = nAttr.create( "output", "out", MFnNumericData::kFloat, 0.0 );
	nAttr.setWritable(false);
	nAttr.setStorable(false);

	stat = addAttribute( input );
		if (!stat) { stat.perror("addAttribute"); return stat;}
	stat = addAttribute( output );
		if (!stat) { stat.perror("addAttribute"); return stat;}

	stat = attributeAffects( input, output );
		if (!stat) { stat.perror("attributeAffects"); return stat;}

	return MS::kSuccess;
}

MStatus initializePlugin(MObject obj) {
	MStatus   status;
	MFnPlugin plugin(obj, "Giulio Martella", "0.1", "Any");

	status = plugin.registerNode(
		"explodeGroup", 
		explodeGroup::id, 
		explodeGroup::creator,
		explodeGroup::initialize);

	if(!status) {
		status.perror("registerNode");
		return status;
	}

	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus   status;
	MFnPlugin plugin( obj );

	status = plugin.deregisterNode( explodeGroup::id );
	if (!status) {
		status.perror("deregisterNode");
		return status;
	}

	return status;
}