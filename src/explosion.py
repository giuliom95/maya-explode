import pymel.core as pmc

n = pmc.createNode('explodeGroup')
grp = pmc.ls(sl=True)[0]

for i,c in enumerate(grp.getChildren()):
    center = c.getAttr('center')
    pmc.setAttr(n.cs[i], center)
    pmc.setAttr(n.ds[i], center - c.getAttr('t'))
    pmc.connectAttr(n.ts[i], c.t)
