function v = InverseKinematicsRotationParametrizationRollPitchYaw()
  persistent vInitialized;
  if isempty(vInitialized)
    vInitialized = iDynTreeMEX(0, 37);
  end
  v = vInitialized;
end
