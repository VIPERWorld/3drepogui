/**
 *  Copyright (C) 2014 3D Repo Ltd
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef REPO_TRANSCODER_ASSIMP_H
#define REPO_TRANSCODER_ASSIMP_H

#include <string>
//------------------------------------------------------------------------------
#include <assimp/scene.h> 
//------------------------------------------------------------------------------
#include <QObject>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QHash>
#include <QColor>
//------------------------------------------------------------------------------
#include <GLC_Material>
#include <GLC_World>
#include "glc_config.h"
#include "geometry/glc_mesh.h"
#include "sceneGraph/glc_structoccurence.h"
#include "maths/glc_geomtools.h"
//------------------------------------------------------------------------------
namespace repo {
namespace gui {

/*!
 * Creates GLC_World instance out of Assimp scene.
 */
class RepoTranscoderAssimp
{
public:

	//! Creates a world instance of a given scene.
	static GLC_World toGLCWorld(
		const aiScene *,
		const std::map<std::string, QImage> &,
		const std::string & namePrefix = "");

	//! Creates a struct occurrence instance out of a given node.
	/*!
	 * Recursive function to create a hierarchy of occurrences of a given 
	 * Assimp node and all of its children. Call with root node to process
	 * the entire scene graph.
	 */
	static GLC_StructOccurence* createOccurrenceFromNode(
		const aiScene * scene, 
		const aiNode * node,
		const QVector<GLC_3DRep*> &glcMeshes,
		const QHash<const QString, GLC_3DRep*> &glcCameras);

    //--------------------------------------------------------------------------
    //
    // Static helpers
    //
    //--------------------------------------------------------------------------

    /*!
     * Returns a GLC Material given an Assimp material and a fileName map of
     * textures.
     */
    static GLC_Material * toGLCMaterial(const aiMaterial *, const QHash<QString, GLC_Texture>&);

    //! Returns a GLC 3DRep given an Assimp mesh and a vector of GLC Materials.
    static GLC_3DRep* toGLCMesh(const aiMesh *, const QVector<GLC_Material*> &,
        const std::string &namePrefix);

    //! Returns a GLC Mesh given an Assimp camera.
    static GLC_3DRep* toGLCCamera(const aiCamera *);

    //--------------------------------------------------------------------------
	//
	// World management
	//
    //--------------------------------------------------------------------------
	//! Copies meshes from a to b.
	//static void copyGLCWorld(const GLC_World& a, GLC_World &b);

	//! Replicates the meshes as new objects.
	//static GLC_StructOccurence * deepCopyOccurence(const GLC_StructOccurence * occurence);

private:

	//! GLC instance Hash table
	//QHash<const unsigned int, GLC_StructInstance*> m_StructInstanceHash;

}; // end class

} // end namespace gui
} // end namespace repo

#endif // end REPO_TRANSCODER_ASSIMP_H