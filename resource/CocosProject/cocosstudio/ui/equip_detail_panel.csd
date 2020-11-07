<GameProjectFile>
  <PropertyGroup Type="Node" Name="equip_detail_panel" ID="1bb968c4-28c2-405d-87be-1eeffa31db53" Version="2.2.9.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="root" Tag="34" ctype="GameNodeObjectData">
        <Size />
        <Children>
          <AbstractNodeData Name="panel" ActionTag="-1378630421" Tag="35" IconVisible="False" LeftMargin="-150.0000" RightMargin="-150.0000" TopMargin="-110.0000" Scale9Enable="True" LeftEage="27" RightEage="27" TopEage="27" BottomEage="27" Scale9OriginX="27" Scale9OriginY="27" Scale9Width="28" Scale9Height="28" ctype="ImageViewObjectData">
            <Size X="300.0000" Y="110.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize />
            <FileData Type="Normal" Path="images/ui/ui_331.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="lbl_item_name" ActionTag="377771503" Tag="192" IconVisible="False" LeftMargin="-122.0000" RightMargin="-28.0000" TopMargin="-104.0000" BottomMargin="76.0000" IsCustomSize="True" FontSize="20" LabelText="物品名称" VerticalAlignmentType="VT_Center" ctype="TextObjectData">
            <Size X="150.0000" Y="28.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="-122.0000" Y="90.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="0" />
            <PrePosition />
            <PreSize X="0.6944" Y="1.0000" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="lbl_item_score" ActionTag="1847964114" Tag="194" IconVisible="False" LeftMargin="-119.0000" RightMargin="-31.0000" TopMargin="-76.0000" BottomMargin="52.0000" IsCustomSize="True" FontSize="20" LabelText="战力:{0}" VerticalAlignmentType="VT_Center" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
            <Size X="150.0000" Y="24.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="-119.0000" Y="64.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.3333" Y="0.2105" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="lbl_item_desc" ActionTag="-1172429614" Tag="195" IconVisible="False" LeftMargin="-122.0000" RightMargin="-178.0000" TopMargin="-49.0000" BottomMargin="5.0000" IsCustomSize="True" FontSize="20" LabelText="Text Label" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
            <Size X="300.0000" Y="44.0000" />
            <AnchorPoint ScaleY="1.0000" />
            <Position X="-122.0000" Y="49.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.6667" Y="0.3860" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="lbl_score_change" ActionTag="1477732848" Tag="196" IconVisible="False" LeftMargin="48.0000" RightMargin="-120.0000" TopMargin="-75.0000" BottomMargin="51.0000" IsCustomSize="True" FontSize="20" LabelText="" VerticalAlignmentType="VT_Center" OutlineSize="1" ShadowOffsetX="2" ShadowOffsetY="-2" ctype="TextObjectData">
            <Size X="72.0000" Y="24.0000" />
            <Children>
              <AbstractNodeData Name="sp_change_up" ActionTag="285798654" Tag="197" IconVisible="False" LeftMargin="-18.5000" RightMargin="77.5000" TopMargin="2.0000" BottomMargin="2.0000" ctype="SpriteObjectData">
                <Size X="13.0000" Y="20.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-12.0000" Y="12.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="-0.1667" Y="0.5000" />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_332.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="sp_change_down" ActionTag="-2081584820" Tag="198" IconVisible="False" LeftMargin="-18.5000" RightMargin="77.5000" TopMargin="2.0000" BottomMargin="2.0000" ctype="SpriteObjectData">
                <Size X="13.0000" Y="20.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-12.0000" Y="12.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="-0.1667" Y="0.5000" />
                <PreSize />
                <FileData Type="Normal" Path="images/ui/ui_333.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleY="0.5000" />
            <Position X="48.0000" Y="63.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.1600" Y="0.2105" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>