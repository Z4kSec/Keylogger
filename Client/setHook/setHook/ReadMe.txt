========================================================================
    BIBLIOTHÈQUE DE LIENS DYNAMIQUES : Vue d'ensemble du projet setHook
========================================================================

AppWizard a créé cette DLL setHook pour vous.

Ce fichier contient un résumé du contenu de chacun des fichiers qui constituent votre application setHook.


setHook.vcxproj
    Il s'agit du fichier projet principal pour les projets VC++ générés à l'aide d'un Assistant Application. Il contient des informations sur la version de Visual C++ utilisée pour générer le fichier ainsi que des informations relatives aux plateformes, configurations et fonctionnalités du projet que vous avez sélectionnées dans l'Assistant Application.

setHook.vcxproj.filters
    Il s'agit du fichier de filtres pour les projets VC++ générés à l'aide d'un Assistant Application. Il contient des informations sur l'association entre les fichiers de votre projet et les filtres. Cette association est utilisée dans l'IDE pour afficher le regroupement des fichiers qui ont des extensions similaires sous un nœud spécifique (par exemple, les fichiers ".cpp" sont associés au filtre "Fichiers sources").

setHook.cpp
    Il s'agit du fichier source principal de la DLL.

	Une fois créée, cette DLL n'exporte aucun symbole. Il en résulte qu'elle ne produira pas un fichier .lib lors de la génération. Si vous souhaitez que ce projet soit une dépendance d'un autre projet, vous devez ajouter du code pour exporter des symboles à partir de la DLL afin qu'une bibliothèque d'exportation soit créée, ou vous pouvez affecter la valeur Yes à la propriété Ignore Input Library dans la page de propriétés Général du dossier Éditeur de liens de la boîte de dialogue Pages de propriétés du projet.

/////////////////////////////////////////////////////////////////////////////
Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers sont utilisés pour générer un fichier d'en-tête précompilé (PCH) setHook.pch et un fichier de type précompilé nommé StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Autres remarques :

AppWizard utilise des commentaires "TODO:" pour indiquer les parties du code source où vous devrez ajouter ou modifier du code.

/////////////////////////////////////////////////////////////////////////////
