vtk_module(vtkIOMPIParallel
  IMPLEMENTS
    vtkIOGeometry
    vtkIOParallel
  GROUPS
    MPI
  DEPENDS
    vtkIOGeometry
    vtkIOParallel
  PRIVATE_DEPENDS
    vtksys
    vtkParallelMPI
  TEST_DEPENDS
    vtkRendering${VTK_RENDERING_BACKEND}
    vtkTestingRendering
    vtkInteractionStyle
  KIT
    vtkParallel
  )
