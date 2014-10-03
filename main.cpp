#include <vtkGeoProjection.h>
#include <vtkGeoTransform.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main()
{
  vtkNew<vtkPolyDataReader> reader;
  reader->SetFileName("continents.vtk");

  vtkNew<vtkGeoProjection> src;
  vtkNew<vtkGeoProjection> dst;
  dst->SetName("robin");

  vtkNew<vtkGeoTransform> transform;
  transform->SetSourceProjection(src.GetPointer());
  transform->SetDestinationProjection(dst.GetPointer());

  reader->Update();
  vtkPolyData *output = reader->GetOutput();
  vtkPoints *inputPoints = output->GetPoints();

  vtkNew<vtkPoints> transformedPoints;
  transform->TransformPoints(inputPoints,
                             transformedPoints.GetPointer());

  output->SetPoints(transformedPoints.GetPointer());

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputData(output);

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper.GetPointer());

  vtkNew<vtkRenderer> ren;
  ren->AddActor(actor.GetPointer());

  vtkNew<vtkRenderWindow> renWin;
  vtkNew<vtkRenderWindowInteractor> interactor;

  renWin->AddRenderer(ren.GetPointer());

  interactor->SetRenderWindow(renWin.GetPointer());
  interactor->Start();

  return 0;
}

