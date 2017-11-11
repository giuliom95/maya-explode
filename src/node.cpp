#include <string.h>
#include <maya/MIOStream.h>
#include <math.h>

#include <maya/MPxNode.h> 

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMessageAttribute.h>
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
	static  MObject		group;
	static  MObject		explosion;
	static  MObject		translations;
	static	MTypeId		id;
};

MTypeId	explodeGroup::id( 0x000ff );
MObject	explodeGroup::group;
MObject	explodeGroup::explosion;
MObject	explodeGroup::translations;

explodeGroup::explodeGroup() {}
explodeGroup::~explodeGroup() {}

MStatus explodeGroup::compute( const MPlug& plug, MDataBlock& data ) {
	
	MStatus returnStatus;
 
	if(plug == explodeGroup::translations)
	{
		cout << "COMPUTING" << endl;
		/*
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
		*/
	} else {
		return MS::kUnknownParameter;
	}

	return MS::kSuccess;
}

void* explodeGroup::creator()
{
	return new explodeGroup();
}

MStatus explodeGroup::initialize()
{
	MFnMessageAttribute mAttr;
	MFnNumericAttribute nAttr;
	MStatus				stat;

	explodeGroup::group = mAttr.create("group", "grp");
	mAttr.setReadable(false);

	explodeGroup::explosion = nAttr.create("explosion", "e", MFnNumericData::kFloat, 1.0 );

	explodeGroup::translations = nAttr.createPoint("translations", "ts");
	nAttr.setArray(true);
	nAttr.setWritable(false);

	// TODO: Here I think I can accomulate the stat vars and chack them once in the end
	stat = addAttribute(explodeGroup::group);
		if (!stat) { stat.perror("addAttribute"); return stat;}
	stat = addAttribute(explodeGroup::explosion);
		if (!stat) { stat.perror("addAttribute"); return stat;}
	stat = addAttribute(explodeGroup::translations);
		if (!stat) { stat.perror("addAttribute"); return stat;}
	
	stat = attributeAffects(explodeGroup::explosion, explodeGroup::translations);
		if (!stat) { stat.perror("attributeAffects"); return stat;}
	stat = attributeAffects(explodeGroup::explosion, explodeGroup::translations);
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