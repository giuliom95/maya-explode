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
	static  MObject		explosion;
	static  MObject		centers;
	static  MObject		translations;
	static	MTypeId		id;
};

MTypeId	explodeGroup::id( 0x000ff );
MObject	explodeGroup::explosion;
MObject explodeGroup::centers;
MObject	explodeGroup::translations;

explodeGroup::explodeGroup() {}
explodeGroup::~explodeGroup() {}

MStatus explodeGroup::compute( const MPlug& plug, MDataBlock& data ) {
	
	MStatus stat;
 
	if(plug == explodeGroup::translations)
	{
		
		auto explosionData = data.inputValue(explodeGroup::explosion, &stat);
		auto centersData = data.inputArrayValue(explodeGroup::centers, &stat);
		
		if( stat != MS::kSuccess )
			cerr << "ERROR getting data" << endl;
		else {
			
			auto outputData = data.outputArrayValue(explodeGroup::translations);

			auto e = explosionData.asFloat();

			do{
				auto cData = centersData.inputValue();
				auto oData = outputData.outputValue();

				auto c = cData.asFloat3();
				oData.set3Float(e*c[0], e*c[1], e*c[2]);

				centersData.next();
			} while(outputData.next());

			data.setClean(plug);
		}
		
		
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
	MFnNumericAttribute nAttr;
	MStatus				stat;

	explodeGroup::explosion = nAttr.create("explosion", "e", MFnNumericData::kFloat, 1.0 );
	nAttr.setMin(1);
	nAttr.setMax(5);

	explodeGroup::centers = nAttr.createPoint("centers", "cs");
	nAttr.setArray(true);
	nAttr.setReadable(false);
	nAttr.setIndexMatters(true);
	nAttr.setHidden(true);

	explodeGroup::translations = nAttr.createPoint("translations", "ts");
	nAttr.setArray(true);
	nAttr.setWritable(false);
	nAttr.setIndexMatters(true);

	// TODO: Here I think I can accomulate the stat vars and chack them once in the end
	stat = addAttribute(explodeGroup::explosion);
		if (!stat) { stat.perror("addAttribute"); return stat;}
	stat = addAttribute(explodeGroup::centers);
		if (!stat) { stat.perror("addAttribute"); return stat;}
	stat = addAttribute(explodeGroup::translations);
		if (!stat) { stat.perror("addAttribute"); return stat;}
	
	stat = attributeAffects(explodeGroup::explosion, explodeGroup::translations);
		if (!stat) { stat.perror("attributeAffects"); return stat;}	
	stat = attributeAffects(explodeGroup::centers, explodeGroup::translations);
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